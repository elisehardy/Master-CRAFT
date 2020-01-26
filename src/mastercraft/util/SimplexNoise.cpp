#include <effolkronium/random.hpp>
#include <glm/ext.hpp>

#include <mastercraft/util/SimplexNoise.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::util {
    
    SimplexNoise::SimplexNoise() :
        seed({ Random::get(-10000, 10000), Random::get(-10000, 10000) }) {
        assert(this->e1 + this->e2 + this->e3 == 1.);
    }
    
    
    SimplexNoise::SimplexNoise(GLfloat t_e1, GLfloat t_e2, GLfloat t_e3) :
        seed({ Random::get(-10000, 10000), Random::get(-10000, 10000) }), e1(t_e1), e2(t_e2), e3(t_e3) {
        assert(this->e1 + this->e2 + this->e3 == 1.);
    }
    
    
    SimplexNoise::SimplexNoise(const glm::vec2 &t_seed) :
        seed(t_seed) {
        assert(this->e1 + this->e2 + this->e3 == 1.);
    }
    
    
    SimplexNoise::SimplexNoise(const glm::vec2 &t_seed, GLfloat t_e1, GLfloat t_e2, GLfloat t_e3) :
        seed(t_seed), e1(t_e1), e2(t_e2), e3(t_e3) {
        assert(this->e1 + this->e2 + this->e3 == 1.);
    }
    
    
    GLfloat SimplexNoise::simplex(const glm::vec2 &p) {
        return static_cast<GLfloat>(glm::simplex(p) * 0.5 + 0.5);
    }
    
    
    GLubyte SimplexNoise::operator()(const glm::vec2 &position) {
        float value = (
            this->e1 * SimplexNoise::simplex(seed + position)
            + this->e2 * SimplexNoise::simplex(2.f * (seed + position))
            + this->e3 * SimplexNoise::simplex(4.f * (seed + position))
        );
        
        return static_cast<GLubyte >(value * 256);
    }
    
    
    GLubyte SimplexNoise::operator()(GLint x, GLint y) {
        return (*this)({ x, y });
    }
}
