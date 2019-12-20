#ifndef MASTERCRAFT_SHADERTEXTURE_HPP
#define MASTERCRAFT_SHADERTEXTURE_HPP

#include <glm/mat4x4.hpp>

#include <mastercraft/shader/Shader.hpp>


namespace mastercraft::shader {
    
    class ShaderTexture : public Shader {
        private:
            GLint uTexture = -1;
            GLuint textureId = 0;
        
        public:
            
            ShaderTexture(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile, std::string texturePath);
            
            void bindTexture() const;
            
            void unbindTexture() const;
    };
}

#endif // MASTERCRAFT_SHADERTEXTURE_HPP

