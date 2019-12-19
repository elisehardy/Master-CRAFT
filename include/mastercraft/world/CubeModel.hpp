#ifndef MASTERCRAFT_CUBEMODEL_HPP
#define MASTERCRAFT_CUBEMODEL_HPP

#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>

#include <mastercraft/util/Singleton.hpp>


namespace mastercraft::world {
    
    class CubeModel : public util::Singleton {
        private:
            CubeModel() = default;
        
        public:
            const glm::vec3 vertices[24] = {
                    // Face
                    { 0, 0, 1, },
                    { 1, 0, 1, },
                    { 1, 1, 1, },
                    { 0, 1, 1, },
                    // Top
                    { 0, 1, 1, },
                    { 1, 1, 1, },
                    { 1, 1, 0, },
                    { 0, 1, 0, },
                    // Back
                    { 1, 0, 0, },
                    { 0, 0, 0, },
                    { 0, 1, 0, },
                    { 1, 1, 0, },
                    // Bottom
                    { 0, 0, 0, },
                    { 1, 0, 0, },
                    { 1, 0, 1, },
                    { 0, 0, 1, },
                    // Left
                    { 0, 0, 0, },
                    { 0, 0, 1, },
                    { 0, 1, 1, },
                    { 0, 1, 0, },
                    // Right
                    { 1, 0, 1, },
                    { 1, 0, 0, },
                    { 1, 1, 0, },
                    { 1, 1, 1, },
            };
            
            const glm::vec3 normals[6] = {
                    // Face
                    { 0.f,  0.f,  -1.f },
                    // Top
                    { 0.f,  1.f,  0.f },
                    // Back
                    { 0.f,  0.f,  1.f },
                    // Bottom
                    { 0.f,  -1.f, 0.f },
                    // Left
                    { -1.f, 0.f,  0.f },
                    // Right
                    { 1.f,  0.f,  0.f },
            };
            
            const glm::vec2 textures[24] = {
                    // Face
                    { 0.0, 0.0, },
                    { 1.0, 0.0, },
                    { 1.0, 1.0, },
                    { 0.0, 1.0, },
                    // Top
                    { 0.0, 0.0, },
                    { 1.0, 0.0, },
                    { 1.0, 1.0, },
                    { 0.0, 1.0, },
                    // Back
                    { 0.0, 0.0, },
                    { 1.0, 0.0, },
                    { 1.0, 1.0, },
                    { 0.0, 1.0, },
                    // Bottom
                    { 0.0, 0.0, },
                    { 1.0, 0.0, },
                    { 1.0, 1.0, },
                    { 0.0, 1.0, },
                    // Left
                    { 0.0, 0.0, },
                    { 1.0, 0.0, },
                    { 1.0, 1.0, },
                    { 0.0, 1.0, },
                    // Right
                    { 0.0, 0.0, },
                    { 1.0, 0.0, },
                    { 1.0, 1.0, },
                    { 0.0, 1.0, },
            };
            
            const GLuint indexes[36] = {
                    // Face
                    0, 1, 2,
                    2, 3, 0,
                    // Top
                    4, 5, 6,
                    6, 7, 4,
                    // Back
                    8, 9, 10,
                    10, 11, 8,
                    // Bottom
                    12, 13, 14,
                    14, 15, 12,
                    // Left
                    16, 17, 18,
                    18, 19, 16,
                    // Right
                    20, 21, 22,
                    22, 23, 20,
            };
            
            static CubeModel &get();
            
            ////////////////////////////// METHODS /////////////////////////////
            
            [[nodiscard]] GLuint size() const;
            
            [[nodiscard]] GLuint verticesCount() const;
            
            [[nodiscard]] GLuint normalsCount() const;
            
            [[nodiscard]] GLuint texturesCount() const;
            
            [[nodiscard]] GLuint indexesCount() const;
    };
}

#endif //MASTERCRAFT_CUBEMODEL_HPP
