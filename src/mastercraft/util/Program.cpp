#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

#include <mastercraft/util/Program.hpp>
#include <mastercraft/util/Uuid.hpp>


static std::string getHeader(const std::string &driver) {
    static std::string header;
    
    if (driver.find("NVIDIA") != std::string::npos) {
        header = "#version 330 core";
    }
    else if (driver.find("Mesa") != std::string::npos) {
        header = "#version 300 es\n\nprecision mediump float;";
    }
    else {
        throw std::runtime_error("Error : Unknown driver : " + driver);
    }
    
    return header;
}


static glimac::FilePath addVersion(const glimac::FilePath &shaderPath) {
    static const std::string driver = std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    static const std::string header = getHeader(driver);
    
    std::ifstream shader = std::ifstream(shaderPath);
    std::string content((std::istreambuf_iterator<char>(shader)), std::istreambuf_iterator<char>());
    shader.close();
    
    content = content.replace(0, 13, header);
    
    glimac::FilePath newPath =
            glimac::FilePath("/tmp/" + mastercraft::util::Uuid::uuid4() + "_" + basename(shaderPath.c_str()));
    std::ofstream tmpShader(newPath);
    tmpShader << content;
    tmpShader.flush();
    tmpShader.close();
    
    return newPath;
}


namespace mastercraft::util {
    
    Program::Program() :
            m_nGLId(glCreateProgram()) {
    }
    
    
    Program::~Program() {
        glDeleteProgram(this->m_nGLId);
    }
    
    
    Program::Program(Program &&rvalue) noexcept:
            m_nGLId(rvalue.m_nGLId) {
        rvalue.m_nGLId = 0;
    }
    
    
    Program &Program::operator=(Program &&rvalue) noexcept {
        this->m_nGLId = rvalue.m_nGLId;
        rvalue.m_nGLId = 0;
        return *this;
    }
    
    
    Program Program::loadProgram(const glimac::FilePath &vsPath, const glimac::FilePath &fsPath) {
        glimac::Shader vs = glimac::loadShader(GL_VERTEX_SHADER, addVersion(vsPath).c_str());
        glimac::Shader fs = glimac::loadShader(GL_FRAGMENT_SHADER, addVersion(fsPath).c_str());
        
        if (!vs.compile()) {
            throw std::runtime_error(
                    "Compilation error for vertex shader (from file " + std::string(vsPath) + "): " + vs.getInfoLog()
            );
        }
        
        if (!fs.compile()) {
            throw std::runtime_error("Compilation error for fragment shader (from file " + std::string(fsPath) + "): "
                                     + fs.getInfoLog());
        }
        
        Program program;
        program.attachShader(vs);
        program.attachShader(fs);
        
        if (!program.link()) {
            throw std::runtime_error(
                    "Link error (for files " + vsPath.str() + " and " + fsPath.str() + "): " + program.getInfoLog());
        }
        
        return program;
    }
    
    
    GLuint Program::getGLId() const {
        return this->m_nGLId;
    }
    
    
    std::string Program::getInfoLog() const {
        GLint length;
        glGetProgramiv(this->m_nGLId, GL_INFO_LOG_LENGTH, &length);
        char *log = new char[length];
        glGetProgramInfoLog(this->m_nGLId, length, nullptr, log);
        std::string logString(log);
        delete[] log;
        return logString;
    }
    
    
    void Program::attachShader(const glimac::Shader &shader) {
        glAttachShader(this->m_nGLId, shader.getGLId());
    }
    
    
    bool Program::link() {
        glLinkProgram(this->m_nGLId);
        GLint status;
        glGetProgramiv(this->m_nGLId, GL_LINK_STATUS, &status);
        return status == GL_TRUE;
    }
    
    
    void Program::use() const {
        glUseProgram(this->m_nGLId);
    }
}
