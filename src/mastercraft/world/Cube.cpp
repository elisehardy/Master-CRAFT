#include <mastercraft/world/Cube.hpp>
#include <mastercraft/world/CubeVertex.hpp>


namespace mastercraft::world {
    
    Cube::Cube(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        
        CubeVertex v[VERTICE_COUNT] = {
            // Face
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, 0, -1 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, 0, -1 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 0, -1 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 0, -1 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 0, -1 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, 0, -1 }, { 0, 0, }, type),
            // Top
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 1, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 1, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 1, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 1, 0 }, { 0, 0, }, type),
            // Back
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, 0, 1 }, { 0, 0, }, type),
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, 0, 1 }, { 1, 0, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 0, 1 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 0, 1 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 0, 1 }, { 0, 1, }, type),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, 0, 1 }, { 0, 0, }, type),
            // Bottom
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, -1, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, -1, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, -1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, -1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, -1, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, -1, 0 }, { 0, 0, }, type),
            // Left
            CubeVertex({ x + 0, y + 0, z + 0 }, { -1, 0, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 0, y + 0, z + 1 }, { -1, 0, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { -1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { -1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { -1, 0, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 0 }, { -1, 0, 0 }, { 0, 0, }, type),
            // Right
            CubeVertex({ x + 1, y + 0, z + 1 }, { 1, 0, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 1, 0, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 1, 0, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 1, 0, 0 }, { 0, 0, }, type),
        };
        
        std::memcpy(this->vertices, v, sizeof(this->vertices));
    }
}
