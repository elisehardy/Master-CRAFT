#ifndef MASTERCRAFT_CUBEFACE_HPP
#define MASTERCRAFT_CUBEFACE_HPP

#include <vector>
#include <cstring>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <mastercraft/cube/CubeType.hpp>
#include <mastercraft/cube/CubeVertex.hpp>


namespace mastercraft::cube {
    
    struct CubeFace {
        
        static constexpr GLuint VERTICE_COUNT = 6;
        
        
        CubeVertex vertices[VERTICE_COUNT];
        
        
        CubeFace() = default;
        
        [[nodiscard]] static CubeFace face(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        [[nodiscard]] static CubeFace face(GLubyte x, GLubyte y, GLubyte z,
            GLfloat sizex, GLfloat sizey, GLfloat sizez, CubeType type);
        
        [[nodiscard]] static CubeFace top(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace back(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace bottom(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace left(GLubyte x, GLubyte y, GLubyte z, CubeType type);
        
        [[nodiscard]] static CubeFace right(GLubyte x, GLubyte y, GLubyte z, CubeType type);
    };
}

#endif //MASTERCRAFT_CUBEFACE_HPP
