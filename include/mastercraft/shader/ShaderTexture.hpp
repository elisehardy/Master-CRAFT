#ifndef MASTERCRAFT_SHADERTEXTURE_HPP
#define MASTERCRAFT_SHADERTEXTURE_HPP

#include <mastercraft/shader/Shader.hpp>
#include <mastercraft/shader/Texture.hpp>


namespace mastercraft::shader {
    
    class ShaderTexture : public Shader {
        private:
            GLint uTexture = -1;
        
        public:
            
            ShaderTexture() = default;
            
            ShaderTexture(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile);
            
            void bindTexture(const Texture &texture) const;
            
            void unbindTexture() const;
    };
}

#endif // MASTERCRAFT_SHADERTEXTURE_HPP

