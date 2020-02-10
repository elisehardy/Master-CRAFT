#ifndef MASTERCRAFT_DEBUG_HPP
#define MASTERCRAFT_DEBUG_HPP

#include <unordered_map>

#include <glm/glm.hpp>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::game {
    
    struct Glyph {
        shader::Texture texture; /**< ID handle of the glyph texture. */
        glm::vec2 size;         /**< Size of glyph. */
        glm::vec2 bearing;      /**< Offset from baseline to left/top of glyph. */
        FT_Pos advance;          /**<  Offset to advance to next glyph. */
        
        Glyph() = default;
        
        Glyph(shader::Texture texture, glm::ivec2 size, glm::ivec2 bearing, FT_Pos advance);
    };
    
    
    
    class Debug : public util::INonCopyable {
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
        
        private:
            std::unique_ptr<shader::ShaderTexture> shader;
            std::unordered_map<FT_ULong, Glyph> glyphs;
            GLuint vbo = 0;
            GLuint vao = 0;
            
            
            void renderText(GLfloat x, GLfloat y, GLfloat scale, const std::string &text, const glm::vec3 &color);
        
        public:
            
            Debug();
            
            ~Debug();
            
            void render();
    };
}

#endif //MASTERCRAFT_DEBUG_HPP
