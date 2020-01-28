#include <mastercraft/shader/Texture.hpp>


namespace mastercraft::texture {
    Texture::Texture(const std::unique_ptr<util::Image> &tex) {
        glGenTextures(1, &this->textureId);
        
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, tex->getWidth(), tex->getHeight(), 0, GL_RGBA, GL_FLOAT, tex->getPixels()
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, this->textureId);
    }
}
