//
// Created by ehardy on 3/2/20.
//

#ifndef MASTERCRAFT_MAGIE2_HPP
#define MASTERCRAFT_MAGIE2_HPP

#include <mastercraft/shader/Shader.hpp>
#include <mastercraft/game/ConfigManager.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>
#include <c3ga/Mvec.hpp>
#include "SphereVertex.hpp"


namespace mastercraft::entity {

    class Magie2 : public util::INonCopyable {
    private:
        static constexpr GLuint VERTEX_ATTR_POSITION = 0;
        static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
        static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;


    private:
        glm::vec3 vertices[36] = {
                // face
                { -1, -1, 1 },
                { 1,  -1, 1 },
                { 1,  1,  1 },
                { 1,  1,  1 },
                { -1, 1,  1 },
                { -1, -1, 1 },
                // top
                { -1, 1,  1 },
                { 1,  1,  1 },
                { 1,  1,  -1 },
                { 1,  1,  -1 },
                { -1, 1,  -1 },
                { -1, 1,  1 },
                // back
                { 1,  -1, -1 },
                { -1, -1, -1 },
                { -1, 1,  -1 },
                { -1, 1,  -1 },
                { 1,  1,  -1 },
                { 1,  -1, -1 },
                // bottom
                { -1, -1, -1 },
                { 1,  -1, -1 },
                { 1,  -1, 1 },
                { 1,  -1, 1 },
                { -1, -1, 1 },
                { -1, -1, -1 },
                // left
                { -1, -1, -1 },
                { -1, -1, 1 },
                { -1, 1,  1 },
                { -1, 1,  1 },
                { -1, 1,  -1 },
                { -1, -1, -1 },
                // right
                { 1,  -1, 1 },
                { 1,  -1, -1 },
                { 1,  1,  -1 },
                { 1,  1,  -1 },
                { 1,  1,  1 },
                { 1,  -1, 1 },
        };

        shader::Texture texture;
        std::unique_ptr<shader::ShaderTexture> shader;


        glm::vec3 position;
        GLuint vbo;
        GLuint vao;

        void computeDirectionVectors();

        GLfloat pitch;           /**< Rotation on X axis */
        GLfloat yaw;             /**< Rotation on Y axis */
        glm::vec3 leftVector;    /**< Vector used to move on X axis */
        glm::vec3 upVector;      /**< Vector used to move on Y axis */
        glm::vec3 frontVector;   /**< Vector used to move on Z axis */


    public:

        Magie2();

        ~Magie2();

        GLuint update();

        GLuint render();

        [[nodiscard]] glm::vec3 getPosition();

        c3ga::Mvec<double> getSphereDual();

        GLboolean isTouch(c3ga::Mvec<double> sphereDual);
        void rotateLeft(float degrees) ;
        void moveLeft(float delta);

        void moveForward(float delta);

        void moveUp(float delta);


        void rotateUp(float degrees);

        void init() ;

        void setPosition(GLfloat x, GLfloat y, GLfloat z);
        c3ga::Mvec<double> getSphere();

        };
}

#endif //MASTERCRAFT_MAGIE2_HPP
