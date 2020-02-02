#include <mastercraft/entity/Slime.hpp>
#include <mastercraft/util/OBJ.hpp>
#include <iostream>
#include <mastercraft/game/Game.hpp>
#include <mastercraft/util/AStarNew.hpp>
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
        IEntity(util::Image::loadPNG("../assets/entity/slime/slime.png", 250, 253), { x, y, z }, 0){
        this->vertices = util::OBJ::Load("../assets/entity/slime/slime.obj");
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao); /*if(this->position == this->destination){
            std::cout << "=======" << std::endl;
            //int max = 0;

            auto v = entity::Slime::generateDest();
            while(!(util::cell::sameChunk(v, this->position))){
                std::cout << "nope" << std::endl;
                v = entity::Slime::generateDest();

            }

            std::cout << "this->position " << this->position.x << " " << this->position.y << " " << this->position.z << std::endl;
            std::cout << "dest " << v.x << " " << v.y << " " << v.z << std::endl;

            auto pathGenerate = util::cell::aStarSearch( this->position, v);
        }*/
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
                dir = Random::get(-2,2);
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

       /* if(this->position == this->destination){
            std::cout << "=======" << std::endl;
            //int max = 0;

            auto v = entity::Slime::generateDest();
            while(!(util::cell::sameChunk(v, this->position))){
                std::cout << "nope" << std::endl;
                v = entity::Slime::generateDest();

            }
            std::cout << "ssssssssssssssssss" << std::endl;

            std::cout << "thi->position " << this->position.x << " " << this->position.y << " " << this->position.z << std::endl;
            std::cout << " v " << v.x << " " << v.y << " " << v.z << std::endl;

            auto pathGenerate = util::cell::aStarSearch( this->position, v);

            *//*while(pathGenerate.empty() && max < 200){
                v = entity::Slime::generateDest();
                pathGenerate = util::cell::aStarSearch(this->position, v);
                max ++;
            }
            this->path = pathGenerate;*//*
        }*/
      /*  if(this->position != this->destination) {
            std::cout << "difff" << std::endl;

            if (!this->path.empty()) {
                this->position = glm::vec3(this->path.top().x, this->path.top().y,
                                           this->path.top().z);
            }
        }*/



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

        //this->path.pop();
        
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

    glm::vec3 Slime::generateDest(){
        game::Game *game = game::Game::getInstance();
        auto coord = game->chunkManager->getSuperChunkCoordinates(this->position);
        auto x = Random::get(coord.x, coord.x+15);
        auto z = Random::get(coord.z, coord.z+15);
        auto y = game->chunkManager->heightSimplex(
                x, z, game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT);
        return glm::vec3(x, y, z);
    }

    glm::vec3 Slime::walk(){
        game::Game *game = game::Game::getInstance();

        switch (this->dir) {
            case 1:{
                return glm::vec3(this->position.x + 1, game->chunkManager->heightSimplex(
                        this->position.x+1, this->position.z, game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z);
            }
            case -1:{
                return glm::vec3(this->position.x - 1, game->chunkManager->heightSimplex(
                        this->position.x-1, this->position.z, game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z);
            }
            case 2:{
                return glm::vec3(this->position.x , game->chunkManager->heightSimplex(
                        this->position.x, this->position.z+1, game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z+1);
            }
            case -2:{
                return glm::vec3(this->position.x, game->chunkManager->heightSimplex(
                        this->position.x, this->position.z-1, game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)+1, this->position.z-1);
            }
            default:{
                return this->position;
            }
        }
    }

    int Slime::canHop(){
        game::Game *game = game::Game::getInstance();
        switch (this->dir) {
            case 1:{
                int h = abs(game->chunkManager->heightSimplex(
                        this->position.x+1, this->position.z,
                        game::ConfigManager::GEN_MIN_HEIGHT,
                        game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2) {
                    return 0;
                }
                else{
                    return -1;
                }
            }
            case -1:{
                int h = abs(game->chunkManager->heightSimplex(
                        this->position.x-1, this->position.z,
                        game::ConfigManager::GEN_MIN_HEIGHT,
                game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2){
                    return 0;
                }
                else{
                    return -1;
                }
            }
            case 2:{
                int h = abs(game->chunkManager->heightSimplex(
                        this->position.x, this->position.z+1,
                        game::ConfigManager::GEN_MIN_HEIGHT,
                game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2){
                    return 0;
                }
                else{
                    return -1;
                }
            }
            case -2:{
                int h = abs(game->chunkManager->heightSimplex(
                        this->position.x, this->position.z-1,
                        game::ConfigManager::GEN_MIN_HEIGHT,
                game::ConfigManager::GEN_MAX_HEIGHT) - this->position.y);
                if(h < 2){
                    return 0;
                }
                else{
                    return -1;
                }
            }
            default:{
                return -1;
            }
        }
    }
}
