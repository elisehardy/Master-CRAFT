//
// Created by ehardy on 2/24/20.
//

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <effolkronium/random.hpp>

#include <mastercraft/entity/Magie.hpp>
#include <mastercraft/util/OBJ.hpp>
#include <mastercraft/game/Game.hpp>
#include <glm/ext.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::entity {

    Magie::Magie(const glm::vec3 &t_position) :

            IEntity(t_position), vertices(std::vector<EntityVertex>()),
            texture(util::Image::loadPNG("../assets/entity/magie/magie.png", 250, 253)),
            direction(glm::vec3(0)), goal(t_position) {
            init(1,32,16);

        this->texture.bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        this->texture.unbind();

        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);


    }

    void Magie::init(GLfloat r, GLsizei discLat, GLsizei discLong) {
        // Equation paramétrique en (r, phi, theta) de la sphère
        // avec r >= 0, -PI / 2 <= theta <= PI / 2, 0 <= phi <= 2PI
        //
        // x(r, phi, theta) = r sin(phi) cos(theta)
        // y(r, phi, theta) = r sin(theta)
        // z(r, phi, theta) = r cos(phi) cos(theta)
        //
        // Discrétisation:
        // dPhi = 2PI / discLat, dTheta = PI / discLong
        //
        // x(r, i, j) = r * sin(i * dPhi) * cos(-PI / 2 + j * dTheta)
        // y(r, i, j) = r * sin(-PI / 2 + j * dTheta)
        // z(r, i, j) = r * cos(i * dPhi) * cos(-PI / 2 + j * dTheta)

        GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
        GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;

        std::vector<EntityVertex> data;

        // Construit l'ensemble des vertex
        for(GLsizei j = 0; j <= discLong; ++j) {
            GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
            GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);

            for(GLsizei i = 0; i <= discLat; ++i) {
                EntityVertex vertex;

                vertex.texture.x = i * rcpLat;
                vertex.texture.y = 1.f - j * rcpLong;

                vertex.normal.x = sin(i * dPhi) * cosTheta;
                vertex.normal.y = sinTheta;
                vertex.normal.z = cos(i * dPhi) * cosTheta;

                vertex.vertex = r * vertex.normal;

                data.push_back(vertex);
            }
        }

        //m_nVertexCount = discLat * discLong * 6;

        //GLuint idx = 0;
        // Construit les vertex finaux en regroupant les données en triangles:
        // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
        // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
        // avec i sur la bande correspondant à la longitude
        for(GLsizei j = 0; j < discLong; ++j) {
            GLsizei offset = j * (discLat + 1);
            for(GLsizei i = 0; i < discLat; ++i) {
                vertices.push_back(data[static_cast<std::vector<int>::size_type>(offset + i)]);
                vertices.push_back(data[static_cast<std::vector<int>::size_type>(offset + (i + 1))]);
                vertices.push_back(data[static_cast<std::vector<int>::size_type>(offset + discLat + 1 + (i + 1))]);
                vertices.push_back(data[static_cast<std::vector<int>::size_type>(offset + i)]);
                vertices.push_back(data[static_cast<std::vector<int>::size_type>(offset + discLat + 1 + (i + 1))]);
                vertices.push_back(data[static_cast<std::vector<int>::size_type>(offset + i + discLat + 1)]);
            }
        }

        // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
        // par un Index Buffer Object, que nous verrons dans les prochains TDs
    }



    Magie::~Magie() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }


    void Magie::walk() {
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


    GLuint Magie::update() {
        //walk();
        game::Game *game = game::Game::getInstance();
        auto pos  = game->camera->getPosition();
        pos.z +=1;
        this->position = pos;
        GLfloat yaw = std::atan2(this->direction.x, this->direction.z);
        glm::mat4 rY = glm::rotate(glm::mat4(1.f), yaw, glm::vec3(0.f, 1.f, 0.f));
        glm::mat4 scale = glm::scale(glm::mat4(0.1f), glm::vec3(1.5f, 1.5f, 1.5f));
        glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0,1,1));
        glm::vec3 positionP ;

        std::vector<EntityVertex> vertices;
        for (const EntityVertex &vertex: this->vertices) {
            positionP =
                    glm::vec3(translate*scale * rY*glm::vec4(vertex.vertex - glm::vec3(0.5), 1))  + this->position;
            positionP -= glm::vec3(0, 0.6, 0);
            vertices.emplace_back(positionP, vertex.normal, vertex.texture);
        }
        //std::cout << position.x << " " << position.y << " " << position.z << std::endl;
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


    GLuint Magie::render() {
        game::Game *game = game::Game::getInstance();

        game->chunkManager->entityShader->bindTexture(this->texture);
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->vertices.size()));
        glBindVertexArray(0);
        game->chunkManager->entityShader->unbindTexture();


        return 1;
    }


    /*c3ga::Mvec<double> Magie::getSphere(){
        auto size  = this->vertices.size();
        auto p1 = this->vertices.at(0).vertex;
        auto p2 = this->vertices.at(1).vertex;
        auto p3 = this->vertices.at(size-1).vertex;
        auto p4 = this->vertices.at(size -2).vertex;

        c3ga::Mvec<double> sphere = point<double>(static_cast<const double>(p1.x),
                                                  static_cast<const double>(p1.y),
                                                  static_cast<const double>(p1.z))
                                    ^point<double>(static_cast<const double>(p2.x),
                                                   static_cast<const double>(p2.y),
                                                   static_cast<const double>(p2.z))
                                    ^point<double>(static_cast<const double>(p3.x),
                                                   static_cast<const double>(p3.y),
                                                   static_cast<const double>(p3.z))
                                    ^point<double>(static_cast<const double>(p3.x),
                                                   static_cast<const double>(p4.y),
                                                   static_cast<const double>(p4.z));
        return sphere;
    }*/

}
