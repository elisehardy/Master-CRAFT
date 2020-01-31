#include <mastercraft/shader/Texture.hpp>


namespace mastercraft::shader {
    
    Texture::Texture(const util::Image *texture) {
        glGenTextures(1, &this->textureId);
        
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, texture->getWidth(), texture->getHeight(), 0,
            GL_RGBA, GL_FLOAT, texture->getPixels()
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    GLuint Texture::getTextureId() const {
        return this->textureId;
    }
}
