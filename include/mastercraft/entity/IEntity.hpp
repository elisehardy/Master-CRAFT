#ifndef MASTERCRAFT_IENTITY_HPP
#define MASTERCRAFT_IENTITY_HPP

#include <stack>

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/shader/Texture.hpp>
#include <mastercraft/util/AStarNew.hpp>


namespace mastercraft::entity {
    
    class IEntity : public util::INonCopyable {
        protected:
            shader::Texture texture;
            glm::vec3 position;
            glm::vec3 destination;
            GLfloat rotation;
            std::stack<glm::dvec4> path;
            
        public:
            IEntity(const util::Image *t_texture, const glm::vec3 &position, GLfloat rotation);
            
            virtual ~IEntity() = default;
            
            virtual GLuint update() = 0;
            
            virtual GLuint render() = 0;
            
            [[nodiscard]] glm::vec3 getPosition() const;


    };
}

#endif //MASTERCRAFT_IENTITY_HPP
