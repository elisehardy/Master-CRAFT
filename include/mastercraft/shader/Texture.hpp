#ifndef MASTERCRAFT_TEXTURE_HPP
#define MASTERCRAFT_TEXTURE_HPP

#include <memory>

#include <GL/glew.h>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/util/Image.hpp>


namespace mastercraft::texture {
    
    class Texture : public util::INonCopyable {
        private:
            GLuint textureId = 0;
        
        public:
            
            explicit Texture(const std::unique_ptr<util::Image> &tex);
            
            void bind() const;
    };
}

#endif //MASTERCRAFT_TEXTURE_HPP
