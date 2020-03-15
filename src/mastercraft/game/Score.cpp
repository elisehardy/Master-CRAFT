//
// Created by ehardy on 3/2/20.
//

#include <stdexcept>
#include <iostream>
#include <iomanip>

#include <glm/gtc/type_ptr.hpp>

#include <mastercraft/game/Score.hpp>
#include <mastercraft/game/Game.hpp>
#include <mastercraft/util/Image.hpp>


namespace mastercraft::game {


    Score::Score() {

        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            throw std::runtime_error("Error: Could not init FreeType");
        }

        FT_Face face;
        if (FT_New_Face(ft, "../assets/GameSystem.ttf", 0, &face)) {
            throw std::runtime_error("Error: Could not load font '../assets/GameSystem.ttf'");
        }
        FT_Set_Pixel_Sizes(face, 0, static_cast<FT_UInt>(LINE_HEIGHT));

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (FT_ULong c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "Error: Failed to load Glyph'" << c << "'" << std::endl;
                continue;
            }

            GLuint textureId;
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RED, static_cast<GLsizei>(face->glyph->bitmap.width),
                    static_cast<GLsizei>(face->glyph->bitmap.rows), 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            this->glyphs.emplace(
                    c,
                    Glyph(
                            shader::Texture(textureId),
                            { face->glyph->bitmap.width, face->glyph->bitmap.rows },
                            { face->glyph->bitmap_left, face->glyph->bitmap_top },
                            face->glyph->advance.x
                    )
            );
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        // Loading shaders
        SDL_DisplayMode display = Game::getInstance()->windowManager->getDisplayMode();
        this->width = static_cast<GLfloat>(display.w);
        this->height = static_cast<GLfloat>(display.h);

        glm::mat4 projection = glm::ortho(0.0f, this->width, 0.0f, this->height);

        this->shader = std::make_unique<shader::ShaderTexture>("../shader/debug.vs.glsl", "../shader/debug.fs.glsl");
        this->shader->addUniform("uProjection", shader::UNIFORM_MATRIX_4F);
        this->shader->addUniform("uTextColor", shader::UNIFORM_3_F);
        this->shader->use();
        this->shader->loadUniform("uProjection", glm::value_ptr(projection));
        this->shader->stop();

        // Generating VBO and VAO
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);

        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    Score::~Score() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }


    void Score::renderText(GLfloat x, GLfloat y, GLfloat scale, const std::string &text, const glm::vec3 &color) {
        this->shader->use();
        this->shader->loadUniform("uTextColor", glm::value_ptr(color));

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->vao);

        GLfloat xpos, ypos, w, h;
        auto start = text.begin();
        auto end = text.end();
        Glyph glyph;
        for (auto c = start; c != end; c++) {
            glyph = this->glyphs[static_cast<FT_ULong>(*c)];

            xpos = x + glyph.bearing.x * scale;
            ypos = y - (glyph.size.y - glyph.bearing.y) * scale;

            w = glyph.size.x * scale;
            h = glyph.size.y * scale;

            GLfloat vertices[6][4] = {
                    { xpos,     ypos + h, 0.0, 0.0 },
                    { xpos,     ypos,     0.0, 1.0 },
                    { xpos + w, ypos,     1.0, 1.0 },
                    { xpos,     ypos + h, 0.0, 0.0 },
                    { xpos + w, ypos,     1.0, 1.0 },
                    { xpos + w, ypos + h, 1.0, 0.0 }
            };

            this->shader->bindTexture(glyph.texture);
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (glyph.advance >> 6) * scale;
        }
        glBindVertexArray(0);
        this->shader->unbindTexture();
    }


    void Score::render() {
        Game *game = Game::getInstance();
        std::stringstream ss;
        glm::vec3 color;


        color = glm::vec3(1) - ConfigManager::getSkyboxColor(game->tickCycle);


        float i = 0;


        ss.str(std::string());
        ss << "Number monster kill: " << game->score->monster_kill;
        this->renderText(10.f, this->height - 40 - LINE_HEIGHT * i++, 1.0f, ss.str(), color);

        ss.str(std::string());
        ss << "life: " << game->score->life;
        this->renderText(10.f, this->height - 40 - LINE_HEIGHT * i++, 1.0f, ss.str(), color);

        ss.str(std::string());
        ss << "life: " << game->score->life2;
        this->renderText(10.f, this->height - 40 - LINE_HEIGHT * i++, 1.0f, ss.str(), color);


        i++;
        ss.str(std::string());
        ss << "Slime: " << game->score->nb_slime;
        this->renderText(10.f, this->height - 40 - LINE_HEIGHT * i++, 1.0f, ss.str(), color);
        ss.str(std::string());
        ss << "Robot: " << game->score->nb_robot;
        this->renderText(10.f, this->height - 40 - LINE_HEIGHT * i++, 1.0f, ss.str(), color);
        ss.str(std::string());
        ss << "Spider: " << game->score->nb_spider;
        this->renderText(10.f, this->height - 40 - LINE_HEIGHT * i++, 1.0f, ss.str(), color);



    }


    void Score::addMonsterKill(GLint type) {
        switch (type){
            case 0:{
                nb_slime++;
                break;
            }
            case 1:{
                nb_robot++;
                break;
            }
            case 2:{
                nb_spider++;
                break;
            }
            default:
                break;
        }
        monster_kill++;
    }


    void Score::removeLife(GLint type) {
        switch (type){
            case 0:{
                life--;
                break;
            }
            case 1:{
                life-=3;
                break;
            }
            case 2:{
                life-=10;
                break;
            }
            default:
                break;
        }
    }

    void Score::quit(){
        Game *game = Game::getInstance();

        if(life <0 || life2 < 0){
            game->stop();
        }
    }


    GLint Score::getMonster_kill() {
        return monster_kill;
    }

    void Score::removeMonsterKill() {
        if(this->monster_kill-3 > 0){
            this->monster_kill-=3;
        }else{
            this->monster_kill = 0;
        }
    }

}
