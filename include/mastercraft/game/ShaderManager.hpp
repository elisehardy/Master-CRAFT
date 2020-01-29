#ifndef MASTERCRAFT_SHADERMANAGER_HPP
#define MASTERCRAFT_SHADERMANAGER_HPP

#include <mastercraft/shader/ShaderTexture.hpp>


namespace mastercraft::game {
    
    struct ShaderManager : public util::INonCopyable {
        std::unique_ptr<shader::ShaderTexture> cubeShader;
        std::unique_ptr<shader::ShaderTexture> entityShader;
        
        
        ShaderManager() = default;
        
        void init();
    };
}

#endif //MASTERCRAFT_SHADERMANAGER_HPP
