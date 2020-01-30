#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include <mastercraft/entity/Sun.hpp>
#include <mastercraft/util/OBJ.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::entity {
    
    Sun::Sun(const glm::vec3 &t_position) :
        shader(std::make_unique<shader::Shader>("../shader/sun.vs.glsl", "../shader/sun.fs.glsl")),
        position(t_position) {
        this->shader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Sun::Sun(GLfloat x, GLfloat y, GLfloat z) :
        Sun(glm::vec3(x, y, z)) {
    }
    
    
    Sun::~Sun() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    GLuint Sun::update() {
        glm::vec3 camera = game::Game::getInstance()->camera->getPosition();
        glm::vec3 vertices[36];
        
        this->position = camera + glm::vec3(0, 0, 20);
        
        for (GLuint i = 0; i < 36; i++) {
            vertices[i] = (this->vertices[i] *5.f + this->position);
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
