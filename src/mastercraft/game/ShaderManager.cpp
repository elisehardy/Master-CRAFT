#include <mastercraft/game/ShaderManager.hpp>


namespace mastercraft::game {
    
    void ShaderManager::init() {
        this->cubeShader = std::make_unique<shader::ShaderTexture>(
            "../shader/cubeShader.vs.glsl", "../shader/cubeShader.fs.glsl"
            );
        this->cubeShader->addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uChunkPosition", shader::UNIFORM_3_F);
        this->cubeShader->addUniform("uTextureVerticalOffset", shader::UNIFORM_1_I);
        
        this->entityShader = std::make_unique<shader::ShaderTexture>(
            "../shader/entityShader.vs.glsl", "../shader/entityShader.fs.glsl"
        );
        this->entityShader->addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->entityShader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->entityShader->addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
    }
}
