#include <mastercraft/entity/IEntity.hpp>


namespace mastercraft::entity {
    
    IEntity::IEntity(const util::Image *t_texture, const glm::vec3 &t_position, GLfloat t_rotation) :
        texture(shader::Texture(t_texture)), position(t_position), destination(position), rotation(t_rotation) {
    }
    
    
    glm::vec3 IEntity::getPosition() const {
        return this->position;
    }

  /*  void IEntity::setPath(std::stack<util::triplet<int, int, int>> pathGenerate){
        this->path = pathGenerate;
    }*/

}
