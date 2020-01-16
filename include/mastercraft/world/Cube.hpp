#ifndef MASTERCRAFT_CUBE_HPP
#define MASTERCRAFT_CUBE_HPP

#include <vector>
#include <cstring>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <mastercraft/world/CubeType.hpp>
#include <mastercraft/world/CubeVertex.hpp>


namespace mastercraft::world {
    
    struct Cube {
        static constexpr GLuint VERTICE_COUNT = 36;
        
        CubeVertex vertices[VERTICE_COUNT];
        
        
        Cube() = default;
        
        Cube(GLubyte x, GLubyte y, GLubyte z, CubeType type);
    };
}

#endif //MASTERCRAFT_CUBE_HPP
