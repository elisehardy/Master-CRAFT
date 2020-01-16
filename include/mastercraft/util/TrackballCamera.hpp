#ifndef MASTERCRAFT_TRACKBALLCAMERA_HPP
#define MASTERCRAFT_TRACKBALLCAMERA_HPP

#include <glm/mat4x4.hpp>
#include <GL/glew.h>


namespace mastercraft::util {
    
    class TrackballCamera {
        private:
            GLfloat x;
            GLfloat y;
            GLfloat z;
            GLfloat rX;
            GLfloat rY;
        
        public:
            TrackballCamera();
        
            void moveFront(float delta);
        
            void moveUp(float delta);
            
            void moveRight(float delta);
        
            void rotateLeft(float degrees);
        
            void rotateUp(float degrees);
            [[nodiscard]] glm::mat4 getViewMatrix() const;
    };
}

#endif // MASTERCRAFT_TRACKBALLCAMERA_HPP
