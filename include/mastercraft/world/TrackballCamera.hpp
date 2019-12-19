#ifndef MASTERCRAFT_TRACKBALLCAMERA_HPP
#define MASTERCRAFT_TRACKBALLCAMERA_HPP

#include <glm/mat4x4.hpp>
#include <GL/glew.h>


namespace mastercraft::world {
    
    class TrackballCamera {
        private:
            GLfloat m_fDistance;
            GLfloat m_fAngleX;
            GLfloat m_fAngleY;
        
        public:
            TrackballCamera();
            
            void moveFront(float delta);
            
            void rotateLeft(float degrees);
            
            void rotateUp(float degrees);
            
            [[nodiscard]] glm::mat4 getViewMatrix() const;
    };
}

#endif // MASTERCRAFT_TRACKBALLCAMERA_HPP
