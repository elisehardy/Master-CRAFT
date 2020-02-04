#include <mastercraft/entity/Slime.hpp>
#include <mastercraft/util/OBJ.hpp>
#include <iostream>
#include <mastercraft/game/Game.hpp>
#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;


namespace mastercraft::entity {
    
    Slime::Slime(const glm::vec3 &t_position) :
        IEntity(util::Image::loadPNG("../assets/entity/slime/slime.png", 250, 253), t_position, 0) {
        this->vertices = util::OBJ::Load("../assets/entity/slime/slime.obj");
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Slime::Slime(GLfloat x, GLfloat y, GLfloat z) :
        IEntity(util::Image::loadPNG("../assets/entity/slime/slime.png", 250, 253), { x, y, z }, 0) {
        this->vertices = util::OBJ::Load("../assets/entity/slime/slime.obj");
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Slime::~Slime() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    GLuint Slime::update() {
        if(cout != 0){
            if(flag == 1 && (Slime::canHop() != -1)){
                this->position = walk();
                cout--;
            }else{
                dir = static_cast<SlimeDirection>(Random::get(-2,2));
                this->rotation = dir*45;
                cout --;
            }
        }else{
            flag = Random::get(0,1);
            if(flag){
                cout = Random::get(0,12);
            }
            else{
                cout = Random::get(0, 3);
            }

        }
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
            (const GLvoid *) (offsetof(EntityVertex, vertex))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(EntityVertex),
            (const GLvoid *) (offsetof(EntityVertex, normal))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(EntityVertex),
            (const GLvoid *) (offsetof(EntityVertex, texture))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        return 1;
    }
    
    
    GLuint Slime::render() {
        game::Game *game = game::Game::getInstance();
        glBindVertexArray(this->vao);
        game->chunkManager->entityShader->bindTexture(this->texture);
        glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
        game->chunkManager->entityShader->unbindTexture();
        glBindVertexArray(0);
        
        return 1;
    }

    glm::vec3 Slime::walk(){
        game::Game *game = game::Game::getInstance();

        switch (this->dir) {
            case TOP:{
                return glm::vec3(this->position.x + 1, game->chunkManager->heightNoise(
                        glm::vec2(this->position.x+1, this->position.z),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z);
            }
            case BOTTOM:{
                return glm::vec3(this->position.x - 1, game->chunkManager->heightNoise(
                        glm::vec2(this->position.x-1, this->position.z),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z);
            }
            case RIGHT:{
                return glm::vec3(this->position.x , game->chunkManager->heightNoise(
                        glm::vec2(this->position.x, this->position.z+1),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z+1);
            }
            case LEFT:{
                return glm::vec3(this->position.x, game->chunkManager->heightNoise(
                        glm::vec2(this->position.x, this->position.z-1),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z-1);
            }
            case None:{
                return this->position;
            }
        }
    }

    int Slime::canHop(){
        game::Game *game = game::Game::getInstance();
        switch (this->dir) {
            case TOP:{
                int h = abs(game->chunkManager->heightNoise(
                        glm::vec2(this->position.x+1, this->position.z),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2) {
                    return 0;
                }
                else{
                    return -1;
                }
            }
            case BOTTOM:{
                int h = abs(game->chunkManager->heightNoise(
                        glm::vec2(this->position.x-1, this->position.z),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2){
                    return 0;
                }
                else{
                    return -1;
                }
            }
            case RIGHT:{
                int h = abs(game->chunkManager->heightNoise(
                        glm::vec2(this->position.x, this->position.z+1),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2){
                    return 0;
                }
                else{
                    return -1;
                }
            }
            case LEFT:{
                int h = abs(game->chunkManager->heightNoise(
                        glm::vec2(this->position.x, this->position.z-1),-1, 1, game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2){
                    return 0;
                }
                else{
                    return -1;
                }
            }
            case None:{
                return -1;
            }
        }
    }
}
