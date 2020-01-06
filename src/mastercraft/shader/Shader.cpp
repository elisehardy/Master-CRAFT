#include <stdexcept>

#include <glimac/glm.hpp>

#include <mastercraft/shader/Shader.hpp>
#include <iostream>


namespace mastercraft::shader {
    
    Shader::Shader(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile) :
            program(util::Program::loadProgram(vsFile, fsFile)) {
        
        this->uMVMatrix = glGetUniformLocation(this->program.getGLId(), "uMVMatrix");
        this->uMVPMatrix = glGetUniformLocation(this->program.getGLId(), "uMVPMatrix");
        this->uNormalMatrix = glGetUniformLocation(this->program.getGLId(), "uNormalMatrix");
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
    
    
    void Shader::use() const {
        this->program.use();
    }
}
