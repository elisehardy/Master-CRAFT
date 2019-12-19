#ifndef MASTERCRAFT_SHADERMULTITEXTURE_HPP
#define MASTERCRAFT_SHADERMULTITEXTURE_HPP

#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.inl>

#include <mastercraft/shader/Shader.hpp>


namespace mastercraft::shader {
    
    template<unsigned int N>
    class ShaderMultiTexture : public Shader {
        private:
            std::vector<GLint> uTextures = {};
        
        public:
            
            ShaderMultiTexture(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile) :
                    Shader(vsFile, fsFile) {
                for (unsigned int i = 0; i < N; i++) {
                    this->uTextures.push_back(tryGettingUniformLocation("uTexture" + std::to_string(i)));
                }
            }
            
            
            void loadTextures() const {
                for (unsigned int i = 0; i < N; i++) {
                    glUniform1i(this->uTextures[i], i);
                }
            }
    };
}

#endif // MASTERCRAFT_SHADERMULTITEXTURE_HPP

