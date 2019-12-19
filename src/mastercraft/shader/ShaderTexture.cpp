#include <mastercraft/shader/ShaderTexture.hpp>


namespace mastercraft::shader {
    
    ShaderTexture::ShaderTexture(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile) :
            Shader(vsFile, fsFile) {
        this->uTexture = tryGettingUniformLocation("uTexture");
    }
    
    
    void ShaderTexture::loadTextures() const {
        glUniform1i(this->uTexture, 0);
    }
}
