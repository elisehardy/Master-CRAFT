#include <glm/ext/matrix_transform.hpp>

#include <mastercraft/util/FreeflyCamera.hpp>


namespace mastercraft::util {

    FreeflyCamera::FreeflyCamera() : m_fPhi(M_PI), m_fTheta(0.0), m_Position(glm::vec3(0.0f)) {
        computeDirectionVectors();
    }

    void FreeflyCamera::computeDirectionVectors(){
        m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
        m_LeftVector = glm::vec3(sin(m_fPhi + (M_PI / 2.0)), 0.f, cos(m_fPhi + (M_PI / 2.0)));
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }

    void FreeflyCamera::moveLeft(float t){
        m_Position += t * m_LeftVector;
    }

    void FreeflyCamera::moveFront(float t){
        m_Position += t * m_FrontVector;
    }
    
    void FreeflyCamera::moveUp(float t){
        m_Position += t * m_UpVector;
    }

    void FreeflyCamera::rotateLeft(float degrees){
        m_fPhi += (degrees*(float)M_PI)/180.f;
    }

    void FreeflyCamera::rotateUp(float degrees){
        m_fTheta += (degrees*(float)M_PI)/180.f;
    }

    glm::mat4 FreeflyCamera::getViewMatrix() const{
        //Point
        return  glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    }
}
