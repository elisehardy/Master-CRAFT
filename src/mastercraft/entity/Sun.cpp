#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include <mastercraft/entity/Sun.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::entity {
    
    Sun::Sun() :
        shader(std::make_unique<shader::Shader>("../shader/sun.vs.glsl", "../shader/sun.fs.glsl")) {
        this->shader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Sun::~Sun() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    GLuint Sun::update() {
        game::Game *game = game::Game::getInstance();
        GLfloat angle = glm::radians(360.f / game::ConfigManager::TICK_CYCLE * game->tickCycle);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.f), angle, glm::vec3(0.f, 0.f, 1.f));
        glm::vec3 position, camera = game->camera->getPosition();
        glm::vec3 vertices[36];
        
        for (GLuint i = 0; i < 36; i++) {
            position = glm::vec3(rotation * glm::vec4(this->vertices[i] + glm::vec3(20, 0, 0), 1)) + camera;
            vertices[i] = position;
        }
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
    
    
    GLuint Sun::render() {
        game::Game *game = game::Game::getInstance();
        glm::mat4 MVMatrix = game->camera->getViewMatrix();
        //        glm::mat4 MVMatrix = glm::mat4(glm::mat3(game->camera->getViewMatrix())); // Remove translation from the MV
        glm::mat4 MVPMatrix = game->camera->getProjMatrix() * MVMatrix;
        
        this->shader->use();
        this->shader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        this->shader->stop();
        return 1;
    }
}
