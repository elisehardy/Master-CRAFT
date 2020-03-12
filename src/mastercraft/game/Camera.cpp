#include <glm/ext/matrix_transform.hpp>

#include <mastercraft/game/Camera.hpp>
#include <glm/ext.hpp>
#include <mastercraft/game/Game.hpp>
#include <iostream>

#ifndef M_PIf32
#define M_PIf32    3.141592653589793238462643383279502884f /* pi */
#endif

#ifndef M_PI_2f32
#define M_PI_2f32  1.570796326794896619231321691639751442f /* pi/2 */
#endif

namespace mastercraft::game {
    
    Camera::Camera() :
        position(glm::vec3(0, ConfigManager::GEN_MAX_HEIGHT + 1, 0)), pitch(0.0), yaw(M_PIf32) {
        computeDirectionVectors();
    }
    
    
    void Camera::init() {
        Game *game = Game::getInstance();

        SDL_DisplayMode display = game->windowManager->getDisplayMode();
        this->setProjectionMatrix(game->configManager->getFov(), display.w, display.h);
        glm::vec3 nextPosition = this->position;


        if(game->chunkManager->get(nextPosition)!= cube::CubeType::AIR) {
           // while (game->chunkManager->get(nextPosition) !=
                 //  cube::CubeType::AIR) { // Next cube is solid, trying he one above
                nextPosition += glm::vec3(0, 1, 0);

            //}
        }
        else {
            // Fall until reaching solid cube
            while (game->chunkManager->get(nextPosition) == cube::CubeType::AIR) {
                nextPosition -= glm::vec3(0, 1, 0);
            }
        }

        auto height = static_cast<GLubyte>(game->chunkManager->heightNoise(
                { position.x , position.z  }, -1, 1, ConfigManager::GEN_MIN_HEIGHT,
                ConfigManager::GEN_MAX_HEIGHT
        ));
        nextPosition.y = height+1;
        this->position = nextPosition;

    }

    void Camera::init2() {
        Game *game = Game::getInstance();
        SDL_DisplayMode display = game->windowManager->getDisplayMode();
        this->setProjectionMatrix(game->configManager->getFov(), display.w, display.h);
        glm::vec3 nextPosition = this->position;


        if(game->chunkManager->get(nextPosition)!= cube::CubeType::AIR) {
            // while (game->chunkManager->get(nextPosition) !=
            //  cube::CubeType::AIR) { // Next cube is solid, trying he one above
            nextPosition += glm::vec3(0, 0.6f*3, 0);
            game->magie->setPositionheight(0.6f*3);

            //}
        }
        else {
            // Fall until reaching solid cube
            while (game->chunkManager->get(nextPosition-glm::vec3(0,1,0)) == cube::CubeType::AIR) {
                nextPosition -= glm::vec3(0, 0.6f, 0);
                game->magie->setPositionheight(-0.6f);
            }
        }

        //nextPosition.y+=0.6f;
        //game->magie->setPositionheight(0.6f);
        this->position = nextPosition;

    }


    
    
    void Camera::computeDirectionVectors() {
        this->frontVector = { cos(this->pitch) * sin(this->yaw), sin(this->pitch), cos(this->pitch) * cos(this->yaw) };
        this->leftVector = { sin(this->yaw + M_PI_2f32), 0.f, cos(this->yaw + M_PI_2f32) };
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
        this->pitch = std::max(std::min(this->pitch, M_PI_2f32), -M_PI_2f32);
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
            glm::radians(fov), static_cast<float>(width) / static_cast<float>(height), 0.1f, 256.f * 32.f
        );
    }
    
    
    glm::mat4 Camera::getViewMatrix() const {
        return glm::lookAt(this->position, this->position + this->frontVector, this->upVector);
    }
    
    
    glm::mat4 Camera::getProjMatrix() const {
        return this->projMatrix;
    }


    c3ga::Mvec<double> Camera::getSphereDual(){
        return dualSphere(double(this->position.x), double(this->position.y), double(this->position.z), double(0.5));
    }

    GLboolean Camera::isTouch(c3ga::Mvec<double> sphereDual){
        c3ga::Mvec<double> sphereDual2 = this->getSphereDual();
        c3ga::Mvec<double> intersection = (sphereDual2 ^ sphereDual).dual();
        double radius  = sqrt(intersection * intersection);
        auto cercle = (radius/(radius*c3ga::Ei)) * (radius/(radius*c3ga::Ei));
        if(cercle >=0.0){
            return true;
        }
        return false;
    }


    GLboolean Camera::isCercle(glm::vec3 pos, double rayon){
        return pos.x>0 && static_cast<double>(pos.x) < static_cast<double>(this->position.x) + rayon && pos.y > 0 && static_cast<double>(pos.y) < static_cast<double>(this->position.y+1) + rayon && pos.z > 0 && static_cast<double>(pos.z) < static_cast<double>(this->position.z) + rayon;
    }
}
