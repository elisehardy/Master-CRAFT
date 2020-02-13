#include <mastercraft/entity/IEntity.hpp>


namespace mastercraft::entity {
    
    IEntity::IEntity(const glm::vec3 &pos): position(pos) {
    }
    
    
    glm::vec3 IEntity::getPosition() {
        return this->position;
    }
}
