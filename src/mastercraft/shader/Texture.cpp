#include <mastercraft/shader/Texture.hpp>


namespace mastercraft::shader {
    
    Texture::Texture(const util::Image *texture) {
        glGenTextures(1, &this->textureId);
        
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(texture->getWidth()),
            static_cast<GLsizei>(texture->getHeight()), 0, GL_RGBA, GL_FLOAT, texture->getPixels()
        );
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    Texture::Texture(GLuint t_textureId) :
        textureId(t_textureId) {
    }
    
    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, this->textureId);
    }
    
    
    void Texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
