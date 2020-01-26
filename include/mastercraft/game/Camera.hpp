#ifndef MASTERCRAFT_CAMERA_HPP
#define MASTERCRAFT_CAMERA_HPP

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::game {
    
    class Camera : public util::INonCopyable {
        private:
            glm::mat4 projMatrix;    /**< Projection matrix of the camera */
            glm::vec3 position;      /**< Position of the camera */
            GLfloat pitch;           /**< Rotation on X axis */
            GLfloat yaw;             /**< Rotation on Y axis */
            glm::vec3 leftVector;    /**< Vector used to move on X axis */
            glm::vec3 upVector;      /**< Vector used to move on Y axis */
            glm::vec3 frontVector;   /**< Vector used to move on Z axis */
            
            void computeDirectionVectors();
            
            
        public:
            
            Camera();
            
            void moveLeft(float delta);
            
            void moveForward(float delta);
            
            void moveUp(float delta);
            
            void rotateLeft(float degrees);
            
            void rotateUp(float degrees);
            
            void setPosition(const glm::vec3 &position);
            
            void setPosition(GLfloat x, GLfloat y, GLfloat z);
            
            [[nodiscard]] glm::vec3 getPosition();
            
            void setAngle(GLfloat pitch, GLfloat yaw);
        
            [[nodiscard]] glm::mat4 getViewMatrix() const;
        
            void setProjectionMatrix(float fov, int width, int height);
            
            [[nodiscard]] glm::mat4 getProjMatrix() const;
    };
}

#endif //MASTERCRAFT_CAMERA_HPP
