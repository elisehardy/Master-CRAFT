#ifndef MASTERCRAFT_CUBEFACE_HPP
#define MASTERCRAFT_CUBEFACE_HPP

#include <vector>
#include <cstring>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <mastercraft/world/CubeType.hpp>
#include <mastercraft/world/CubeVertex.hpp>


namespace mastercraft::world {
    
    struct CubeFace {
        
        static constexpr GLuint VERTICE_COUNT = 6;
        
        
        CubeVertex vertices[VERTICE_COUNT];
        
        
        CubeFace() = default;
        
        [[nodiscard]] static CubeFace face(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace top(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace back(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace bottom(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace left(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace right(GLubyte x, GLubyte y, GLubyte z, CubeType type);
    };
}

#endif //MASTERCRAFT_CUBEFACE_HPP
