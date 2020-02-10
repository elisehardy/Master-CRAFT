#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include <mastercraft/entity/Skybox.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::entity {
    
    Skybox::Skybox() {
        std::unique_ptr<util::Image> texture[6] = {
            std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/day_side.png", 512, 512)),
            std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/day_side.png", 512, 512)),
            std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/day_top.png", 512, 512)),
            std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/day_bottom.png", 512, 512)),
            std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/day_side.png", 512, 512)),
            std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/day_side.png", 512, 512)),
        };
        this->day = std::make_unique<shader::Cubemap>(texture);
        
        texture[0] = std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/night_right.png", 512, 512));
        texture[1] = std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/night_left.png", 512, 512));
        texture[2] = std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/night_top.png", 512, 512));
        texture[3] = std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/night_bottom.png", 512, 512));
        texture[4] = std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/night_back.png", 512, 512));
        texture[5] = std::unique_ptr<util::Image>(util::Image::loadPNG("../assets/entity/skybox/night_front.png", 512, 512));
        this->night = std::make_unique<shader::Cubemap>(texture);
        
        this->shader = std::make_unique<shader::ShaderCubemap>("../shader/skybox.vs.glsl", "../shader/skybox.fs.glsl");
        this->shader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Skybox::~Skybox() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    GLuint Skybox::update() {
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        return 1;
    }
    
    
    GLuint Skybox::render() {
        game::Game *game = game::Game::getInstance();
        glm::mat4 MVMatrix = glm::mat4(glm::mat3(game->camera->getViewMatrix())); // Remove translation from the MV
        glm::mat4 MVPMatrix = game->camera->getProjMatrix() * MVMatrix;
    
        glCullFace(GL_FRONT);
        this->shader->use();
        this->shader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        this->shader->bindCubemap(game->tickCount < game::ConfigManager::TICK_DAY ? *this->day : *this->night);
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        this->shader->unbindCubemap();
        this->shader->stop();
        glCullFace(GL_BACK);
        
        return 1;
    }
}
