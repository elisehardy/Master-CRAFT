#include <algorithm>
#include <iostream>

#include <mastercraft/shader/Shader.hpp>
#include <mastercraft/shader/uniform/uniform_all.hpp>


namespace mastercraft::shader {
    
    Shader::Shader(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile) :
        program(util::Program::loadProgram(vsFile, fsFile)) {
    }
    
    
    void Shader::addUniform(const std::string &name, UniformType type) {
        std::shared_ptr<IUniform> uniform;
        
        switch (type) {
            case UNIFORM_1_F:
                uniform = std::make_shared<Uniform1fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_2_F:
                uniform = std::make_shared<Uniform2fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_3_F:
                uniform = std::make_shared<Uniform3fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_4_F:
                uniform = std::make_shared<Uniform4fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_1_I:
                uniform = std::make_shared<Uniform1iv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_2_I:
                uniform = std::make_shared<Uniform2iv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_3_I:
                uniform = std::make_shared<Uniform3iv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_4_I:
                uniform = std::make_shared<Uniform4iv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_1_UI:
                uniform = std::make_shared<Uniform1uiv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_2_UI:
                uniform = std::make_shared<Uniform2uiv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_3_UI:
                uniform = std::make_shared<Uniform3uiv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_4_UI:
                uniform = std::make_shared<Uniform4uiv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_2F:
                uniform = std::make_shared<UniformMatrix2fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_3F:
                uniform = std::make_shared<UniformMatrix3fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_4F:
                uniform = std::make_shared<UniformMatrix4fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_2X3F:
                uniform = std::make_shared<UniformMatrix2x3fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_3X2F:
                uniform = std::make_shared<UniformMatrix3x2fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_2X4F:
                uniform = std::make_shared<UniformMatrix2x4fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_4X2F:
                uniform = std::make_shared<UniformMatrix4x2fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_3X4F:
                uniform = std::make_shared<UniformMatrix3x4fv>(this->program.getGLId(), name.c_str());
                break;
            case UNIFORM_MATRIX_4X3F:
                uniform = std::make_shared<UniformMatrix4x3fv>(this->program.getGLId(), name.c_str());
                break;
        }
        
        this->uniforms.emplace(name, uniform);
    }
    
    
    void Shader::loadUniform(const std::string &name, const void *value) {
        try {
            this->uniforms.at(name)->load(value);
        } catch (const std::out_of_range &e) {
            std::cerr << "Error: Trying to specify the value of a non-existent uniform variable '" << name
                      << "' of program '" << this->program.getGLId() << "'." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    
    void Shader::use() const {
        this->program.use();
    }
}
