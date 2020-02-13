#ifndef MASTERCRAFT_IENTITY_HPP
#define MASTERCRAFT_IENTITY_HPP

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::entity {
    
    class IEntity : public util::INonCopyable {
        
        protected:
            glm::vec3 position;
        
        public:
            
            IEntity(const glm::vec3 &pos);
            
            virtual ~IEntity() = default;
            
            virtual GLuint update() = 0;
            
            virtual GLuint render() = 0;
            
            [[nodiscard]] glm::vec3 getPosition();
    };
}
#endif //MASTERCRAFT_IENTITY_HPP
