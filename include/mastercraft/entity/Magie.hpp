//
// Created by ehardy on 2/24/20.
//

#ifndef RECONSTRUCTION3D_MAGIE_HPP
#define RECONSTRUCTION3D_MAGIE_HPP
#include <string>
#include <vector>

#include <glm/vec2.hpp>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/entity/IEntity.hpp>
#include <mastercraft/entity/EntityVertex.hpp>
#include <mastercraft/shader/Texture.hpp>
#include <mastercraft/game/ConfigManager.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>

namespace mastercraft::entity {

    class Magie : public IEntity {
    private:
        static constexpr GLuint VERTEX_ATTR_POSITION = 0;
        static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
        static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;

        static constexpr GLfloat SPEED = 1.f / game::ConfigManager::TICK_PER_SEC * 4.f;

    private:
        std::vector<EntityVertex> vertices;
        std::unique_ptr<shader::ShaderTexture> shader;
        shader::Texture texture;
        glm::vec3 direction;
        glm::vec3 goal;
        GLuint vbo;
        GLuint vao;

        void walk();

    public:

        explicit Magie(const glm::vec3 &position);

        ~Magie();

        void init(GLfloat r, GLsizei discLat, GLsizei discLong);

        GLuint update();

        GLuint render();
        //c3ga::Mvec<double> getSphere();

        };
}

#endif //RECONSTRUCTION3D_MAGIE_HPP
