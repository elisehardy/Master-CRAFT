#include <lodepng/lodepng.hpp>

#include <mastercraft/util/Image.hpp>
#include <iostream>


namespace mastercraft::util {
    
    Image::Image(unsigned int t_width, unsigned int t_height, std::vector<glm::vec4> t_pixels) :
        width(t_width), height(t_height), pixels(std::move(t_pixels)) {
    }
    
    
    Image *Image::loadPNG(const std::string &path, GLuint width, GLuint height) {
        std::vector<glm::vec4> pixels;
        std::vector<GLubyte> raw;
        
        GLuint error = lodepng::decode(raw, width, height, path);
        if (error) {
            std::cerr << "Error: Could not load image '" << path << "': " << lodepng_error_text(error) << std::endl;
            exit(EXIT_FAILURE);
        }
        
        float scale = 1.f / 255.f;
        for (GLuint64 i = 0; i < raw.size(); i += 4) {
            pixels.emplace_back(raw[i] * scale, raw[i + 1] * scale, raw[i + 2] * scale, raw[i + 3] * scale);
        }
        
        return new Image(width, height, pixels);
    }
    
    
    GLuint Image::getWidth() const {
        return width;
    }
    
    
    GLuint Image::getHeight() const {
        return height;
    }
    
    
    const glm::vec4 *Image::getPixels() const {
        return pixels.data();
    }
    
    
    glm::vec4 *Image::getPixels() {
        return pixels.data();
    }
}
