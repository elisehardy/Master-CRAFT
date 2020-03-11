#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <effolkronium/random.hpp>

#include <mastercraft/entity/Spider.hpp>
#include <mastercraft/util/OBJ.hpp>
#include <mastercraft/game/Game.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::entity {

    Spider::Spider(const glm::vec3 &t_position) :
        IEntity(t_position), vertices(util::OBJ::Load("../assets/entity/spider/spider.obj")),
            texture(util::Image::loadPNG("../assets/entity/spider/spider.png", 256, 256)),
            direction(glm::vec3(0)), goal(t_position) {

        this->texture.bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        this->texture.unbind();

        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }


    Spider::~Spider() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }


    void Spider::walk() {
        if (glm::vec2(this->position.x, this->position.z) == glm::vec2(this->goal.x, this->goal.z)) {
            if (Random::get<bool>(0.99)) { // If at goal, 99% chance of idling each tick
                return;
            }

            // Compute another goal
            this->goal = {
                    Random::get<float>(this->position.x - 25, this->position.x + 25),
                    0,
                    Random::get<float>(this->position.z - 25, this->position.z + 25)
            };
        }

        // Compute direction vector
        this->direction = this->goal - glm::vec3(this->position.x, 0, this->position.z);
        if (glm::length(this->direction) > 1.f) {
            this->direction = glm::normalize(this->direction) * SPEED;
        }

        game::Game *game = game::Game::getInstance();
        glm::vec3 nextPosition = this->position + this->direction;

        if (game->chunkManager->get(nextPosition) != cube::CubeType::AIR) { // Next cube is solid, trying he one above
            nextPosition += glm::vec3(0, 1, 0);

            // If next cube height is more than 1, make the robot idle by setting goal to its position
            if (game->chunkManager->get(nextPosition) != cube::CubeType::AIR) {
                this->goal = this->position;
                return;
            }
        }
        else {
            // Fall until reaching solid cube
            while (game->chunkManager->get(nextPosition - glm::vec3(0, 1, 0)) == cube::CubeType::AIR) {
                nextPosition -= glm::vec3(0, 1, 0);
            }
        }

        this->position = nextPosition;
    }


    GLuint Spider::update() {
        walk();

        GLfloat yaw = std::atan2(this->direction.x, this->direction.z);
        glm::mat4 rY = glm::rotate(glm::mat4(1.f), yaw , glm::vec3(0.f, 1.f, 0.f));
        glm::mat4 scale = glm::scale( glm::mat4(1.f), glm::vec3(0.01f,0.01f,0.01f));
        glm::vec3 position;

        std::vector<EntityVertex> vertices;
        for (const EntityVertex &vertex: this->vertices) {
            position = glm::vec3(scale * rY * glm::vec4(vertex.vertex - glm::vec3(0.5), 1)) + glm::vec3(0.5) + this->position;
            vertices.emplace_back(position, vertex.normal, vertex.texture);
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


    GLuint Spider::render() {
        game::Game *game = game::Game::getInstance();

        glBindVertexArray(this->vao);
        game->chunkManager->entityShader->bindTexture(this->texture);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->vertices.size()));
        game->chunkManager->entityShader->unbindTexture();
        glBindVertexArray(0);

        return 1;
    }


    c3ga::Mvec<double> Spider::getSphereDual(){
        return dualSphere(double(this->position.x+0.6f), double(this->position.y+1), double(this->position.z+0.6f), double(0.2));
    }


    GLint Spider::getType(){
        return 2;
    }

    c3ga::Mvec<double> Spider::getSphere(){
        glm::vec3 p1 = vertices[0].vertex;
        glm::vec3 p2 = vertices[1].vertex;
        glm::vec3 p3 = vertices[vertices.size()-1].vertex;
        glm::vec3 p4 = vertices[vertices.size()-2].vertex;
        c3ga::Mvec<double> sphere = point(double(p1.x),double(p1.y),double(p1.z)) ^ point(double(p2.x),double(p2.y),double(p2.z)) ^point(double(p3.x),double(p3.y),double(p3.z)) ^point(double(p4.x),double(p4.y),double(p4.z));
        return sphere;
    }

    GLboolean Spider::isTouch(c3ga::Mvec<double> sphereDual){
        return false;
    }
}
