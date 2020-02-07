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
        tinyobj::real_t vx, vy, vz, nx, ny, nz, tx, ty;
        tinyobj::attrib_t attrib;
        GLuint index_offset, fv;
        std::string warn, err;
        GLuint64 v, n, t;
        
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
                
                for (GLuint i = 0; i < fv; i++) {
                    tinyobj::index_t index = shape.mesh.indices[index_offset + i];
                    v = 3ul * static_cast<GLuint64>(index.vertex_index);
                    n = 3ul * static_cast<GLuint64>(index.normal_index);
                    t = 2ul * static_cast<GLuint64>(index.texcoord_index);
                    
                    vx = attrib.vertices[v + 0];
                    vy = attrib.vertices[v + 1];
                    vz = attrib.vertices[v + 2];
                    nx = attrib.normals[n + 0];
                    ny = attrib.normals[n + 1];
                    nz = attrib.normals[n + 2];
                    tx = attrib.texcoords[t + 0];
                    ty = attrib.texcoords[t + 1];
                    
                    vertices.push_back(entity::EntityVertex({ vx, vy, vz }, { nx, ny, nz }, { tx, ty }));
                }
                index_offset += fv;
            }
        }
        
        return vertices;
    }
}
