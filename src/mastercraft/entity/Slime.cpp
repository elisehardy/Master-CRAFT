#include <mastercraft/entity/Slime.hpp>
#include <mastercraft/util/OBJ.hpp>
#include <iostream>
#include <mastercraft/game/Game.hpp>
#include <effolkronium/random.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::entity {
    
    Slime::Slime(const glm::vec3 &t_position) :
        texture(util::Image::loadPNG("../assets/entity/slime/slime.png", 250, 253)), position(t_position){//, rotation(0) {
        this->vertices = util::OBJ::Load("../assets/entity/slime/slime.obj");
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Slime::~Slime() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    GLuint Slime::update() {
        walk();
        
        std::vector<EntityVertex> vertices;
        
        for (const EntityVertex &vertex: this->vertices) {
            vertices.push_back(vertex + this->position);
        }
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(EntityVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glVertexAttribPointer(
            VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(EntityVertex),
            reinterpret_cast<const GLvoid *>(offsetof(EntityVertex, vertex))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(EntityVertex),
            reinterpret_cast<const GLvoid *>(offsetof(EntityVertex, normal))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(EntityVertex),
            reinterpret_cast<const GLvoid *>(offsetof(EntityVertex, texture))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        return 1;
    }
    
    
    void Slime::walk() {
        if (this->position == this->goal) {
            if (Random::get<bool>(0.95)) { // If at goal, 95% chance of idling each tick
                return;
            }
            
            // Compute another goal
            this->goal = {
                Random::get(position.x - 10, position.x + 10),
                0,
                Random::get(position.z - 10, position.z + 10)
            };
            this->direction = glm::normalize(this->goal - this->position) * SPEED;
            this->direction.y = 0;
        }
        
        game::Game *game = game::Game::getInstance();
        glm::vec3 nextPosition = this->position + this->direction;
        
        if (game->chunkManager->get(nextPosition) != cube::CubeType::AIR) { // Next cube is solid, trying he one above
            nextPosition += glm::vec3(0, 1, 0);
    
            // If next cube height is more than 1, make the slime idle by setting goal to its position
            if (game->chunkManager->get(nextPosition) != cube::CubeType::AIR) {
                this->goal = this->position;
                return;
            }
        }
        
        this->position = nextPosition;
    }
    
    
    GLuint Slime::render() {
        game::Game *game = game::Game::getInstance();
        glBindVertexArray(this->vao);
        game->chunkManager->entityShader->bindTexture(this->texture);
        glDrawArrays(GL_TRIANGLES, 0, GLsizei(this->vertices.size()));
        game->chunkManager->entityShader->unbindTexture();
        glBindVertexArray(0);
        
        return 1;
    }
}
