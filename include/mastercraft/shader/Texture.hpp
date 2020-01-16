#ifndef MASTERCRAFT_TEXTURE_HPP
#define MASTERCRAFT_TEXTURE_HPP

#include <memory>

#include <glimac/Image.hpp>
#include <GL/glew.h>

#include <mastercraft/util/NonCopyable.hpp>


namespace mastercraft::texture {
    
    class Texture : public util::NonCopyable {
        private:
            GLuint textureId = 0;
        
        public:
            explicit Texture(const std::unique_ptr <glimac::Image> &texture);
            
            
            void bind() const;
    };
}

#endif //MASTERCRAFT_TEXTURE_HPP
