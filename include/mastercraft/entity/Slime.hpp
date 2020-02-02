#ifndef MASTERCRAFT_SLIME_HPP
#define MASTERCRAFT_SLIME_HPP

#include <string>
#include <vector>

#include <glm/vec2.hpp>

#include <mastercraft/entity/IEntity.hpp>
#include "EntityVertex.hpp"


namespace mastercraft::entity {
    
    class Slime : public IEntity {
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
            static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
            static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;
        
        private:
            std::vector<EntityVertex> vertices;
            GLuint vbo;
            GLuint vao;
            int flag=0;
            int cout = 0;
            int dir = 0;

        public:
            
            explicit Slime(const glm::vec3 &position);
            
            Slime(GLfloat x, GLfloat y, GLfloat z);
            
            ~Slime() final;
            
            GLuint update() final;
            
            GLuint render() final;

            glm::vec3 generateDest();

            glm::vec3 walk();
            int canHop();

        };
}

#endif //MASTERCRAFT_SLIME_HPP
