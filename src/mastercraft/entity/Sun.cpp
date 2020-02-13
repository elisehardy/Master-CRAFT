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
//        glm::vec3 vertices[36];
//
//        for (GLuint i = 0; i < 36; i++) {
//            vertices[i] = this->vertices[i];
//        }
//
    std::cout << "UPDATE MAGUEULE" << std::endl;
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
    
    
    GLuint Sun::render() {
        game::Game *game = game::Game::getInstance();
        glm::mat4 MVMatrix = game->camera->getViewMatrix();
//        glm::mat4 MVMatrix = glm::mat4(glm::mat3(game->camera->getViewMatrix())); // Remove translation from the MV
        glm::mat4 MVPMatrix = game->camera->getProjMatrix() * MVMatrix;
        std::cout << "RENDER MAGUEULE" << std::endl;
    
        this->shader->use();
        this->shader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        this->shader->stop();
        return 1;
    }
}
