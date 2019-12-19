#include <mastercraft/world/TrackballCamera.hpp>

#include <glm/ext/matrix_transform.hpp>


namespace mastercraft::world {
    
    TrackballCamera::TrackballCamera() :
            m_fDistance(5), m_fAngleX(0), m_fAngleY(0) {
    }
    
    
    void TrackballCamera::moveFront(float delta) {
        this->m_fDistance += delta;
    }
    
    
    void TrackballCamera::rotateLeft(float degrees) {
        this->m_fAngleX += degrees;
    }
    
    
    void TrackballCamera::rotateUp(float degrees) {
        this->m_fAngleY += degrees;
    }
    
    
    glm::mat4 TrackballCamera::getViewMatrix() const {
        glm::mat4 t, rx, ry, i = glm::mat4(1);
        float d = M_PI / 180.;
        
        t = glm::translate(i, glm::vec3(0., 0., -this->m_fDistance));
        ry = glm::rotate(i, this->m_fAngleY * d, glm::vec3(1., 0., 0.));
        rx = glm::rotate(i, this->m_fAngleX * d, glm::vec3(0., 1., 0.));
        
        return t * rx * ry;
    }
}
