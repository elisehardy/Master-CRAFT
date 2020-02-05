#ifndef MASTERCRAFT_SHADERCUBEMAP_HPP
#define MASTERCRAFT_SHADERCUBEMAP_HPP

#include <mastercraft/shader/Shader.hpp>
#include <mastercraft/shader/Cubemap.hpp>


namespace mastercraft::shader {
    
    class ShaderCubemap : public Shader {
        private:
            GLint uTexture = -1;
        
        public:
            
            ShaderCubemap() = default;
            
            ShaderCubemap(const std::string &vsFile, const std::string &fsFile);
            
            void bindCubemap(const Cubemap &texture) const;
            
            void unbindCubemap() const;
    };
}

#endif // MASTERCRAFT_SHADERCUBEMAP_HPP

