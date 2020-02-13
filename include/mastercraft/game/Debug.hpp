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
        glm::vec2 size;          /**< Size of glyph. */
        glm::vec2 bearing;       /**< Offset from baseline to left/top of glyph. */
        FT_Pos advance;          /**< Offset to advance to next glyph. */
        
        Glyph() = default;
        
        Glyph(shader::Texture texture, glm::ivec2 size, glm::ivec2 bearing, FT_Pos advance);
    };
    
    
    
    class Debug : public util::INonCopyable {
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
            static constexpr GLfloat LINE_HEIGHT = 26;
        
        private:
            std::unique_ptr<shader::ShaderTexture> shader; /**< Shader use to render the debug information. */
            std::unordered_map<FT_ULong, Glyph> glyphs;    /**< Table containing information for each ASCII character */
            GLfloat height; /**< Height of the screen. */
            GLfloat width;  /**< Width of the screen. */
            GLuint vbo = 0; /**< VBO use to render the debug menu. */
            GLuint vao = 0; /**< VAO use to render the debug menu. */
            
            void renderText(GLfloat x, GLfloat y, GLfloat scale, const std::string &text, const glm::vec3 &color);
        
        public:
            
            Debug();
            
            ~Debug();
            
            void render();
    };
}

#endif //MASTERCRAFT_DEBUG_HPP
