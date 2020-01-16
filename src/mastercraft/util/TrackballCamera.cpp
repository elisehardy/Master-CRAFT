#include <mastercraft/util/TrackballCamera.hpp>

#include <glm/ext/matrix_transform.hpp>


namespace mastercraft::util {
    
    TrackballCamera::TrackballCamera() :
        x(0), y(0), z(5), rX(0), rY(0) {
    }
    
    
    void TrackballCamera::moveFront(float delta) {
        this->z -= delta;
    }
    
    void TrackballCamera::moveUp(float delta) {
        this->y += delta;
    }
    
    void TrackballCamera::moveRight(float delta) {
        this->x += delta;
    }
    
    
    void TrackballCamera::rotateLeft(float degrees) {
        this->rX += degrees;
    }
    
    
    void TrackballCamera::rotateUp(float degrees) {
        this->rY += degrees;
    }
    
    
    glm::mat4 TrackballCamera::getViewMatrix() const {
        glm::mat4 t, rx, ry, i = glm::mat4(1);
        float d = M_PI / 180.;
        
        t = glm::translate(i, glm::vec3(-this->x, -this->y, -this->z));
        rx = glm::rotate(i, this->rX * d, glm::vec3(0., 1., 0.));
        ry = glm::rotate(i, this->rY * d, glm::vec3(1., 0., 0.));
        
        return t * rx * ry;
    }
}
