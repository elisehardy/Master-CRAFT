#ifndef MASTERCRAFT_SUN_HPP
#define MASTERCRAFT_SUN_HPP

#include <mastercraft/shader/Shader.hpp>
#include <mastercraft/game/ConfigManager.hpp>


namespace mastercraft::entity {
    
    class Sun : public util::INonCopyable {
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
        
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
            std::unique_ptr<shader::Shader> shader;
            glm::vec3 position;
            GLuint vbo;
            GLuint vao;
        
        public:
            
            Sun();
            
            ~Sun();
            
            GLuint update();
            
            GLuint render();
            
            [[nodiscard]] glm::vec3 getPosition();
    };
}

#endif //MASTERCRAFT_SUN_HPP
