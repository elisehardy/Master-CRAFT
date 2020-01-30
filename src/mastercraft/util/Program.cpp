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
    
    Program::Program(const glimac::FilePath &vsPath, const glimac::FilePath &fsPath) {
        this->id = glCreateProgram();
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
        
        this->attachShader(vs);
        this->attachShader(fs);
        
        if (!this->link()) {
            throw std::runtime_error("Link error (for files " + vsPath.str() + " and " + fsPath.str() + "): " + this->getInfoLog());
        }
    }
    
    
    Program::~Program() {
        glDeleteProgram(this->id);
    }
    
    
    
    GLuint Program::getId() const {
        return this->id;
    }
    
    
    std::string Program::getInfoLog() const {
        std::string logString;
        GLint length;
        char *log;
        
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &length);
        log = new char[length];
        glGetProgramInfoLog(this->id, length, nullptr, log);
        logString = log;
        delete[] log;
        
        return logString;
    }
    
    
    void Program::attachShader(const glimac::Shader &shader) {
        glAttachShader(this->id, shader.getGLId());
    }
    
    
    bool Program::link() {
        GLint status;
        glLinkProgram(this->id);
        glGetProgramiv(this->id, GL_LINK_STATUS, &status);
        return status == GL_TRUE;
    }
    
    
    void Program::use() const {
        glUseProgram(this->id);
    }
    
    
    void Program::stop() const {
        glUseProgram(0);
    }
}
