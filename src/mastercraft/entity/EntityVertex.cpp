#include <mastercraft/entity/EntityVertex.hpp>


namespace mastercraft::entity {
    
    EntityVertex::EntityVertex(glm::vec3 t_vertex, glm::vec3 t_normal, glm::vec2 t_texture) :
        vertex(t_vertex), normal(t_normal), texture(t_texture) {
    }
    
    
    EntityVertex EntityVertex::operator+(const glm::vec3 &position) const {
        return EntityVertex(this->vertex + position, this->normal, this->texture);
    }
}
