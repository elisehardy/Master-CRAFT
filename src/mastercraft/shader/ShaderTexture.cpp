#include <mastercraft/shader/ShaderTexture.hpp>


namespace mastercraft::shader {
    
    ShaderTexture::ShaderTexture(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile) :
        Shader(vsFile, fsFile) {
         this->uTexture = glGetUniformLocation(this->program->getId(), "uTexture");
    }
    
    
    void ShaderTexture::bindTexture(const Texture &texture) const {
        glUniform1i(this->uTexture, 0);
        glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    }
    
    
    void ShaderTexture::unbindTexture() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
