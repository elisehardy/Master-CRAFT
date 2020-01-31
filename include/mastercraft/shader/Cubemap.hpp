#ifndef MASTERCRAFT_CUBEMAP_HPP
#define MASTERCRAFT_CUBEMAP_HPP

#include <memory>

#include <GL/glew.h>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/util/Image.hpp>


namespace mastercraft::shader {
    
    class Cubemap : public util::INonCopyable {
        private:
            GLuint textureId = 0;
        
        public:
            
            Cubemap() = default;
            
            explicit Cubemap(std::unique_ptr<util::Image> texture[6]);
            
            [[nodiscard]] GLuint getCubemapId() const;
    };
}

#endif // MASTERCRAFT_CUBEMAP_HPP
