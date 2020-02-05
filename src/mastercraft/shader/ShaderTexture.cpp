#include <mastercraft/shader/ShaderTexture.hpp>


namespace mastercraft::shader {
    
    ShaderTexture::ShaderTexture(const std::string &vsFile, const std::string &fsFile) :
        Shader(vsFile, fsFile) {
         this->uTexture = glGetUniformLocation(this->programId, "uTexture");
    }
    
    
    void ShaderTexture::bindTexture(const Texture &texture) const {
        glUniform1i(this->uTexture, 0);
        glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    }
    
    
    void ShaderTexture::unbindTexture() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
