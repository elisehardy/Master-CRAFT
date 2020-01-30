#include <effolkronium/random.hpp>
#include <glm/ext.hpp>

#include <mastercraft/util/SimplexNoise.hpp>
#include <iostream>


using Random = effolkronium::random_static;

namespace mastercraft::util {
    
    SimplexNoise::SimplexNoise() :
        seed({ Random::get<float>(0., 1000.), Random::get<float>(0., 1000.) }) {
    }
    
    
    GLfloat SimplexNoise::simplex(const glm::vec2 &p) {
        return (glm::simplex(p) + 1) * 0.5f;
    }
    
    
    GLfloat SimplexNoise::toRange(GLfloat value, GLfloat oldMin, GLfloat oldMax, GLfloat newMin, GLfloat newMax) {
        GLfloat oldRange = (oldMax - oldMin);
        GLfloat newRange = (newMax - newMin);
        
        return (((value - oldMin) * newRange) / oldRange) + newMin;
    }
    
    
    GLfloat SimplexNoise::operator()(const glm::vec2 &position, GLfloat min, GLfloat max) {
        GLfloat e1 = 1.f, e2 = 0.25f, e3 = 0.15f;
        glm::vec2 n = (seed + position)/ 256.f;
        GLfloat value = (
            e1 * SimplexNoise::simplex(n)
            + e2 * SimplexNoise::simplex(n * 2.f)
            + e3 * SimplexNoise::simplex(n * 4.f)
        );
        value /= e1 + e2 + e3;
        value = std::pow(value, 3);

        return SimplexNoise::toRange(value, 0, 1, min, max);
    }
    
    
    GLfloat SimplexNoise::operator()(GLfloat x, GLfloat y, GLfloat min, GLfloat max) {
        return (*this)({ x, y }, min, max);
    }
}
