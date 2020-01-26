

#include <mastercraft/cube/CubeFace.hpp>


namespace mastercraft::cube {

    
    CubeFace cube::CubeFace::face(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        CubeFace face;
        
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, 0, -1 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, 0, -1 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 0, -1 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 0, -1 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 0, -1 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, 0, -1 }, { 0, 0, }, type),
        };
    
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::top(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        CubeFace face;
    
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 1, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 0, 1, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 1, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { 0, 1, 0 }, { 0, 0, }, type),
        };
    
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::back(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        CubeFace face;
    
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, 0, 1 }, { 0, 0, }, type),
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, 0, 1 }, { 1, 0, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 0, 1 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { 0, 0, 1 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 0, 0, 1 }, { 0, 1, }, type),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, 0, 1 }, { 0, 0, }, type),
        };
    
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::bottom(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        CubeFace face;
    
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, -1, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 0, -1, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, -1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 0, -1, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 1 }, { 0, -1, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 0 }, { 0, -1, 0 }, { 0, 0, }, type),
        };
    
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::left(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        CubeFace face;
    
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 0, y + 0, z + 0 }, { -1, 0, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 0, y + 0, z + 1 }, { -1, 0, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { -1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 1 }, { -1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 0, y + 1, z + 0 }, { -1, 0, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 0, y + 0, z + 0 }, { -1, 0, 0 }, { 0, 0, }, type),
        };
    
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
    
    
    CubeFace CubeFace::right(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        CubeFace face;
    
        CubeVertex v[VERTICE_COUNT] = {
            CubeVertex({ x + 1, y + 0, z + 1 }, { 1, 0, 0 }, { 0, 0, }, type),
            CubeVertex({ x + 1, y + 0, z + 0 }, { 1, 0, 0 }, { 1, 0, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 0 }, { 1, 0, 0 }, { 1, 1, }, type),
            CubeVertex({ x + 1, y + 1, z + 1 }, { 1, 0, 0 }, { 0, 1, }, type),
            CubeVertex({ x + 1, y + 0, z + 1 }, { 1, 0, 0 }, { 0, 0, }, type),
        };
    
        std::memcpy(face.vertices, v, sizeof(face.vertices));
        return face;
    }
}
