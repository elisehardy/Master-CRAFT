//
// Created by ehardy on 3/8/20.
//

#include <mastercraft/entity/SphereVertex.hpp>

SphereVertex::SphereVertex(const glm::vec3 &t_vertex, const glm::vec3 &t_normal, const glm::vec2 &t_texture) :
        vertex(t_vertex), normal(t_normal), texture(t_texture) {
}
