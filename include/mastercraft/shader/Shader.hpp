#ifndef MASTERCRAFT_SHADER_HPP
#define MASTERCRAFT_SHADER_HPP

#include <glm/mat4x4.hpp>

#include <mastercraft/util/Program.hpp>
#include <mastercraft/util/NonCopyable.hpp>


namespace mastercraft::shader {
    
    class Shader : public util::NonCopyable {
        private:
            GLint uMVMatrix = -1;
            GLint uMVPMatrix = -1;
            GLint uNormalMatrix = -1;
        
        protected:
            util::Program program;
        
        public:
            
            Shader(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile);
            
            void loadModelViewMatrix(glm::mat4 matrix) const;
            
            void loadModelViewProjectionMatrix(glm::mat4 matrix) const;
            
            void loadNormalMatrix(glm::mat4 matrix) const;
            
            void loadMatrices(glm::mat4 mv, glm::mat4 mvp, glm::mat4 normal) const;
            
            void use() const;
    };
}

#endif // MASTERCRAFT_SHADER_HPP

