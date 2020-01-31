#include <mastercraft/shader/ShaderCubemap.hpp>


namespace mastercraft::shader {
    
    ShaderCubemap::ShaderCubemap(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile) :
        Shader(vsFile, fsFile) {
         this->uTexture = glGetUniformLocation(this->program->getId(), "uTexture");
    }
    
    
    void ShaderCubemap::bindCubemap(const Cubemap &texture) const {
        glUniform1i(this->uTexture, 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture.getCubemapId());
    }
    
    
    void ShaderCubemap::unbindCubemap() const {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}
