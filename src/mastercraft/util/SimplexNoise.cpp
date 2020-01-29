#include <effolkronium/random.hpp>
#include <glm/ext.hpp>

#include <mastercraft/util/SimplexNoise.hpp>
#include <iostream>


using Random = effolkronium::random_static;

namespace mastercraft::util {
    
    SimplexNoise::SimplexNoise() :
        seed({ Random::get<float>(0., 1000.), Random::get<float>(0., 1000.) }) {
    }
    
    
    SimplexNoise::SimplexNoise(const glm::vec2 &t_seed) :
        seed(t_seed) {
    }
    
    
    GLfloat SimplexNoise::simplex(const glm::vec2 &p) {
        return static_cast<GLfloat>(glm::simplex(p) * 0.5 + 0.5);
    }
    
    
    GLfloat SimplexNoise::toRange(GLfloat value, GLfloat oldMin, GLfloat oldMax, GLfloat newMin, GLfloat newMax) {
        GLfloat oldRange = (oldMax - oldMin);
        GLfloat newRange = (newMax - newMin);
        
        return (((value - oldMin) * newRange) / oldRange) + newMin;
    }
    
    
    GLfloat SimplexNoise::operator()(const glm::vec2 &position, GLfloat min, GLfloat max) {
        GLfloat e1 = 0.75, e2 = 0.20, e3 = 0.10;
        
        GLfloat value = (
            e1 * SimplexNoise::simplex((seed + position) / 256.f)
            + e2 * SimplexNoise::simplex((seed + position) / 128.f)
            + e3 * SimplexNoise::simplex((seed + position) / 64.f)
        );
        value /= e1 + e2 + e3;
        
        value = std::pow(value, 4);
        return SimplexNoise::toRange(value, 0, 1, min, max);
    }
    
    
    GLfloat SimplexNoise::operator()(GLfloat x, GLfloat y, GLfloat min, GLfloat max) {
        return (*this)({ x, y }, min, max);
    }
}
