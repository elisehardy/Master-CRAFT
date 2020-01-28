#ifndef MASTERCRAFT_IMAGE_HPP
#define MASTERCRAFT_IMAGE_HPP

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <glm/vec4.hpp>

#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::util {
    
    class Image : public INonCopyable {
        
        private:
            GLuint width;
            GLuint height;
            std::vector<glm::vec4> pixels;
        
        public:
            
            Image(GLuint width, GLuint height, std::vector<glm::vec4> t_pixels);
            
            static Image *loadPNG(const std::string &path, GLuint width, GLuint height);
            
            [[nodiscard]] GLuint getWidth() const;
            
            [[nodiscard]] GLuint getHeight() const;
            
            [[nodiscard]] const glm::vec4 *getPixels() const;
            
            [[nodiscard]] glm::vec4 *getPixels();
    };
}

#endif //MASTERCRAFT_IMAGE_HPP
