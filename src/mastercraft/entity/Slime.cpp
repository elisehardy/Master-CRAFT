#include <mastercraft/entity/Slime.hpp>
#include <mastercraft/util/OBJ.hpp>
#include <iostream>
#include <mastercraft/game/Game.hpp>
#include <mastercraft/util/AStarNew.hpp>



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
        if(this->position == this->destination){
            auto v = entity::Slime::generateDest(position.x, position.x+16, position.z, position.z+16);


            auto pathGenerate = util::cell::aStarSearch( this->position, v);

            while(pathGenerate.empty()){
                v = entity::Slime::generateDest(position.x, position.x+16, position.z, position.z+16);
                pathGenerate = util::cell::aStarSearch(this->position, v);

            }
            this->path = pathGenerate;
        }
        if(this->position != this->destination){
            this->position = this->path.top();
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

        this->path.pop();
        
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

    glm::vec3 Slime::generateDest(int maxX, int minX, int maxY, int minY){
        game::Game *game = game::Game::getInstance();
        auto x = rand()%(maxX-minX+1) + minX;
        auto y = rand()%(maxY-minY+1) + minY;
        auto z = game->chunkManager->heightSimplex(
                x, y, game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT);
        return glm::vec3(x, y, z);
    }

}
