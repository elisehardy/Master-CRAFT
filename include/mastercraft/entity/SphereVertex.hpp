//
// Created by ehardy on 3/8/20.
//

#ifndef MASTERCRAFT_SPHEREVERTEX_HPP
#define MASTERCRAFT_SPHEREVERTEX_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


struct SphereVertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 texture;

    SphereVertex() = default;

    SphereVertex(const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &texture);
};
#endif //MASTERCRAFT_SPHEREVERTEX_HPP
