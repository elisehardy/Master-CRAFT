#ifndef MASTERCRAFT_TEXTURE_HPP
#define MASTERCRAFT_TEXTURE_HPP

#include <memory>

#include <GL/glew.h>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/util/Image.hpp>


namespace mastercraft::shader {
    
    class Texture  {
        private:
            GLuint textureId = 0;
        
        public:
            
            Texture() = default;
            
            explicit Texture(const util::Image *texture);
            
            explicit Texture(GLuint textureId);
        
            void bind() const;
            
            void unbind() const;
    };
}

#endif //MASTERCRAFT_TEXTURE_HPP
