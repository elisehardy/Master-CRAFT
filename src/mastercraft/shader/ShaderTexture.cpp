#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/util/Image.hpp>


namespace mastercraft::shader {
    
    ShaderTexture::ShaderTexture(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile,
                                 const util::Image *texture) :
        Shader(vsFile, fsFile) {
        this->uTexture = glGetUniformLocation(this->program.getGLId(), "uTexture");
        
        glGenTextures(1, &this->textureId);
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->getWidth(), texture->getHeight(), 0, GL_RGBA, GL_FLOAT,
                     texture->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    void ShaderTexture::bindTexture() const {
        glUniform1i(this->uTexture, 0);
        glBindTexture(GL_TEXTURE_2D, this->textureId);
    }
    
    
    void ShaderTexture::unbindTexture() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
