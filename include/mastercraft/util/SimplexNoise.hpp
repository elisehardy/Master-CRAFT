#ifndef MASTERCRAFT_SIMPLEXNOISE_HPP
#define MASTERCRAFT_SIMPLEXNOISE_HPP

#include <GL/glew.h>
#include <glm/vec2.hpp>


namespace mastercraft::util {
    
    class SimplexNoise {
        private:
            glm::vec2 seed;
            float e1 = 0.46;
            float e2 = 0.33;
            float e3 = 0.21;
            
            /**
             * Narrow glm's simplex to [0, 1] and to float.
             *
             * @param p Parameter given to glm::simplex().
             *
             * @return Result of glm::simplex() narrowed to [0, 1] as a float.
             */
            static GLfloat simplex(const glm::vec2 &p);
            
        public:
            
            SimplexNoise();
            
            SimplexNoise(GLfloat e1, GLfloat e2, GLfloat e3);
            
            explicit SimplexNoise(const glm::vec2 &seed);
            
            explicit SimplexNoise(const glm::vec2 &seed, GLfloat e1, GLfloat e2, GLfloat e3);
        
            GLubyte operator()(const glm::vec2 &position);
        
            GLubyte operator()(GLint x, GLint y);
    };
}

#endif //MASTERCRAFT_SIMPLEXNOISE_HPP
