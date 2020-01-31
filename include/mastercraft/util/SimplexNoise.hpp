#ifndef MASTERCRAFT_SIMPLEXNOISE_HPP
#define MASTERCRAFT_SIMPLEXNOISE_HPP

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace mastercraft::util {
    
    class SimplexNoise {
        private:
            glm::vec2 seed;
            
            /**
             * Narrow glm's simplex to [0, 1] and to float.
             *
             * @param p Parameter given to glm::simplex().
             *
             * @return Result of glm::simplex() narrowed to [0, 1] as a float.
             */
            static GLfloat simplex(const glm::vec2 &p);
            
            static GLfloat simplex(const glm::vec3 &p);
            
            /**
             * Convert a value from a range to another range, maintaining the same ratio.
             *
             * @param value Value to be converted.
             * @param oldMin Minimum value of the old range.
             * @param oldMax Maximum value of the old range.
             * @param newMin Minimum value of the new range.
             * @param newMax Maximum value of the new range.
             *
             * @return The value converted to the new range.
             */
            static GLfloat toRange(GLfloat value, GLfloat oldMin, GLfloat oldMax, GLfloat newMin, GLfloat newMax);
            
        public:
            
            SimplexNoise();
            
            GLfloat operator()(const glm::vec2 &position, GLint min = 0, GLint max = 0);
            
            GLfloat operator()(GLfloat x, GLfloat y, GLint min = 0, GLint max = 0);
        
            GLfloat operator()(GLfloat x, GLfloat y, GLfloat z);
            
            GLfloat operator()(const glm::vec3 &position);
    };
}

#endif //MASTERCRAFT_SIMPLEXNOISE_HPP
