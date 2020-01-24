#ifndef MASTERCRAFT_CUBEVERTEX_HPP
#define MASTERCRAFT_CUBEVERTEX_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <mastercraft/world/CubeType.hpp>


namespace mastercraft::world {
    
    typedef glm::tvec3<GLbyte> bvec3;
    typedef glm::tvec2<GLbyte> bvec2;
    
    
    
    struct CubeVertex {
        bvec3 vertex;
        bvec3 normal;
        bvec2 texture;
        CubeType type;
        
        CubeVertex() = default;
        
        CubeVertex(bvec3 vertex, bvec3 normal, bvec2 texture, CubeType type = CubeType::AIR);
    };
}
#endif // MASTERCRAFT_CUBEVERTEX_HPP
