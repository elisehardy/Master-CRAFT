#ifndef MASTERCRAFT_SUN_HPP
#define MASTERCRAFT_SUN_HPP

#include <mastercraft/shader/Shader.hpp>


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
            
            explicit Sun(const glm::vec3 &position);
            
            Sun(GLfloat x, GLfloat y, GLfloat z);
            
            ~Sun();
            
            GLuint update();
            
            GLuint render();
    };
}

#endif //MASTERCRAFT_SUN_HPP
