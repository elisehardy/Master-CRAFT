#ifndef MASTERCRAFT_SHADERMANAGER_HPP
#define MASTERCRAFT_SHADERMANAGER_HPP

#include <mastercraft/shader/ShaderTexture.hpp>


namespace mastercraft::game {
    
    struct ShaderManager : public util::INonCopyable {
        std::shared_ptr<shader::ShaderTexture> cubeShader;
        
        
        ShaderManager() = default;
    };
}

#endif //MASTERCRAFT_SHADERMANAGER_HPP
