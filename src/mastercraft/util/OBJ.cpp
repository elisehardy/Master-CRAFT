#define TINYOBJLOADER_IMPLEMENTATION

#include <iostream>

#include <tinyobjloader/tinyobjloader.hpp>
#include <GL/glew.h>

#include <mastercraft/util/OBJ.hpp>


namespace mastercraft::util {

    
    
    std::vector<entity::EntityVertex> OBJ::Load(const std::string &path) {
        std::vector<entity::EntityVertex> vertices;
        std::vector<tinyobj::material_t> materials;
        std::vector<tinyobj::shape_t> shapes;
        tinyobj::attrib_t attrib;
        GLuint index_offset, fv;
        std::string warn, err;
    
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
        if (!warn.empty()) {
            std::cerr << warn << std::endl;
        }
        if (!err.empty()) {
            std::cerr << err << std::endl;
        }
        if (!ret) {
            exit(1);
        }
    
        for (auto &shape : shapes) {
            index_offset = 0;
            for (GLuint f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
                fv = shape.mesh.num_face_vertices[f];
            
                for (GLuint v = 0; v < fv; v++) {
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                    tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
                    tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
                    tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
                    tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
                    tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
                    
                    vertices.push_back(entity::EntityVertex({vx, vy, vz}, {nx, ny, nz}, {tx, ty}));
                }
                index_offset += fv;
            }
        }
        
        return vertices;
    }
}
