#include <mastercraft/world/CubeVertex.hpp>


namespace mastercraft::world {
    
    CubeVertex::CubeVertex(bvec3 t_vertex, bvec3 t_normal, bvec2 t_texture, CubeType t_type) :
        vertex(t_vertex), normal(t_normal), texture(t_texture), type(t_type) {
    }
}


