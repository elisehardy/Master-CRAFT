#ifndef MASTERCRAFT_SLIME_HPP
#define MASTERCRAFT_SLIME_HPP

#include <string>
#include <vector>

#include <glm/vec2.hpp>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/entity/EntityVertex.hpp>
#include <mastercraft/shader/Texture.hpp>


namespace mastercraft::entity {
    
    class Slime : public util::INonCopyable {
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
            static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
            static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;
            static constexpr GLfloat SPEED = 0.5;
        
        private:
            std::vector<EntityVertex> vertices;
            shader::Texture texture;
            glm::vec3 direction;
            glm::vec3 position;
//            GLfloat rotation;
            glm::vec3 goal;
            GLuint vbo;
            GLuint vao;
        
        public:
            
            explicit Slime(const glm::vec3 &position);
            
            ~Slime();
            
            void walk();
            
            GLuint update();
            
            GLuint render();
    };
}

#endif //MASTERCRAFT_SLIME_HPP
