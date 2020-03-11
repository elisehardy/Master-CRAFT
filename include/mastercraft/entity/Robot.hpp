
#ifndef MASTERCRAFT_ROBOT_HPP
#define MASTERCRAFT_ROBOT_HPP

#include <string>
#include <vector>

#include <glm/vec2.hpp>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/entity/IEntity.hpp>
#include <mastercraft/entity/EntityVertex.hpp>
#include <mastercraft/shader/Texture.hpp>
#include <mastercraft/game/ConfigManager.hpp>


namespace mastercraft::entity {

class Robot : public IEntity {
    private:
        static constexpr GLuint VERTEX_ATTR_POSITION = 0;
        static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
        static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;

        static constexpr GLfloat SPEED = 1.f / game::ConfigManager::TICK_PER_SEC * 4.f;

    private:
        std::vector<EntityVertex> vertices;
        shader::Texture texture;
        glm::vec3 direction;
        glm::vec3 goal;
        GLuint vbo;
        GLuint vao;

        void walk();

    public:

        explicit Robot(const glm::vec3 &position);

        ~Robot();

        GLuint update();

        GLuint render();

    c3ga::Mvec<double> getSphereDual();

    GLint getType();

    c3ga::Mvec<double> getSphere();
    c3ga::Mvec<double> getLine();


    GLboolean isTouch(c3ga::Mvec<double> sphereDual);


};
}


#endif //MASTERCRAFT_ROBOT_HPP
