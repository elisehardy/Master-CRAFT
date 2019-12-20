#ifndef MASTERCRAFT_SHADERMULTITEXTURE_HPP
#define MASTERCRAFT_SHADERMULTITEXTURE_HPP

#include <memory>
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.inl>

#include <mastercraft/shader/Shader.hpp>
#include <glimac/Image.hpp>


namespace mastercraft::shader {
    
    template<unsigned int N>
    class ShaderMultiTexture : public Shader {
        private:
            GLint uTextures[N] = -1;
            GLuint textureId[N] = 0;
        
        public:
            
            ShaderMultiTexture(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile,
                               std::string texturePath[N]) :
                    Shader(vsFile, fsFile) {
                
                glGenTextures(N, this->textureId);
                
                for (unsigned int i = 0; i < N; i++) {
                    this->uTexture[i] = glGetUniformLocation(this->program.getGLId(), "uTexture" + std::to_string(i));
                    
                    std::unique_ptr<glimac::Image> texture = glimac::loadImage(texturePath[i]);
                    glBindTexture(GL_TEXTURE_2D, this->textureId[i]);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->getWidth(), texture->getHeight(), 0, GL_RGBA,
                                 GL_FLOAT, texture->getPixels());
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
            }
            
            
            void loadTextures() const {
                for (unsigned int i = 0; i < N; i++) {
                    glActiveTexture(GL_TEXTURE0 + i, this->uTextures[i]);
                    glBindTexture(GL_TEXTURE_2D, this->textureId[i]);
                }
            }
    };
}

#endif // MASTERCRAFT_SHADERMULTITEXTURE_HPP

