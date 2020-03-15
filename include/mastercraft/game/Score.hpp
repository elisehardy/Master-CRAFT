//
// Created by ehardy on 3/2/20.
//

#ifndef MASTERCRAFT_SCORE_HPP
#define MASTERCRAFT_SCORE_HPP

#include <unordered_map>

#include <glm/glm.hpp>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include "Debug.hpp"

#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::game {



    class Score : public util::INonCopyable {
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
        GLint monster_kill = 0;
        GLint nb_slime = 0;
        GLint nb_robot = 0;
        GLint nb_spider = 0;
        GLint life = 10000;


        void renderText(GLfloat x, GLfloat y, GLfloat scale, const std::string &text, const glm::vec3 &color);

    public:
        GLint life2 = 0;

        Score();

        ~Score();

        void render();

        void addMonsterKill(GLint type);
        void removeLife(GLint type) ;
        GLint getMonster_kill();
        void removeMonsterKill();
        void quit();


        };
}

#endif //MASTERCRAFT_SCORE_HPP
