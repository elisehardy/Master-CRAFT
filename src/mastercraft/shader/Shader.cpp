#include <stdexcept>

#include <glimac/glm.hpp>

#include <mastercraft/shader/Shader.hpp>


namespace mastercraft::shader {
    
    GLint Shader::tryGettingUniformLocation(const std::string &varname) const {
        GLint location = glGetUniformLocation(this->program.getGLId(), varname.c_str());
        
        if (location < 0) {
            if (varname.substr(0, 3) == "gl_") {
                throw std::runtime_error("Error: '" + varname + "' starts with the reserved prefix \"gl_\"");
            }
            throw std::runtime_error(
                    "Error: '" + varname + "' does not correspond to an active uniform variable in program,"
                    + " or is associated with an atomic counter or a named uniform block."
            );
        }
        
        return location;
    }
    
    
    Shader::Shader(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile) :
            program(util::Program::loadProgram(vsFile, fsFile)) {
        
        this->uMVMatrix = tryGettingUniformLocation("uMVMatrix");
        this->uMVPMatrix = tryGettingUniformLocation("uMVPMatrix");
        this->uNormalMatrix = tryGettingUniformLocation("uNormalMatrix");
    }
    
    
    void Shader::loadModelViewMatrix(glm::mat4 matrix) const {
        glUniformMatrix4fv(this->uMVMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    
    
    void Shader::loadModelViewProjectionMatrix(glm::mat4 matrix) const {
        glUniformMatrix4fv(this->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    
    
    void Shader::loadNormalMatrix(glm::mat4 matrix) const {
        glUniformMatrix4fv(this->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    
    
    void Shader::loadMatrices(glm::mat4 mv, glm::mat4 mvp, glm::mat4 normal) const {
        loadModelViewMatrix(mv);
        loadModelViewProjectionMatrix(mvp);
        loadNormalMatrix(normal);
    }
}
