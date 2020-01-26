#include <glm/ext/matrix_transform.hpp>

#include <mastercraft/game/Camera.hpp>
#include <glm/ext.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    Camera::Camera() :
        position(glm::vec3(0)), pitch(0.0), yaw(M_PI) {
        computeDirectionVectors();
    }
    
    
    void Camera::computeDirectionVectors() {
        this->frontVector = { cos(this->pitch) * sin(this->yaw), sin(this->pitch), cos(this->pitch) * cos(this->yaw) };
        this->leftVector = { sin(this->yaw + M_PI_2), 0.f, cos(this->yaw + M_PI_2) };
        this->upVector = glm::cross(this->frontVector, this->leftVector);
    }
    
    
    void Camera::moveLeft(float delta) {
        this->position += delta * this->leftVector;
    }
    
    
    void Camera::moveForward(float delta) {
        this->position += delta * this->frontVector;
    }
    
    
    void Camera::moveUp(float delta) {
        this->position += delta * this->upVector;
    }
    
    
    void Camera::rotateLeft(float degrees) {
        this->yaw += glm::radians(degrees * Game::getInstance()->configManager->getMouseSensitivity());
        computeDirectionVectors();
    }
    
    
    void Camera::rotateUp(float degrees) {
        this->pitch += glm::radians(degrees * Game::getInstance()->configManager->getMouseSensitivity());
        computeDirectionVectors();
    }
    
    
    void Camera::setPosition(const glm::vec3 &position) {
        this->position = position;
    }
    
    
    void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z) {
        this->position = { x, y, z };
    }
    
    
    glm::vec3 Camera::getPosition() {
        return this->position;
    }
    
    
    void Camera::setAngle(GLfloat pitch, GLfloat yaw) {
        this->pitch = pitch;
        this->yaw = yaw;
    }
    
    
    void Camera::setProjectionMatrix(float fov, int width, int height) {
        this->projMatrix = glm::perspective(
            glm::radians(fov), static_cast<float>(width) / static_cast<float>(height), 0.1f, 256.f * cube::SuperChunk::X
        );
    }
    
    
    glm::mat4 Camera::getViewMatrix() const {
        return glm::lookAt(this->position, this->position + this->frontVector, this->upVector);
    }
    
    
    glm::mat4 Camera::getProjMatrix() const {
        return this->projMatrix;
    }
}
