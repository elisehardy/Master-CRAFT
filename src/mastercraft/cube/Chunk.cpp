#include <iostream>

#include <mastercraft/cube/Chunk.hpp>
#include <mastercraft/cube/CubeFace.hpp>


namespace mastercraft::cube {
    
    Chunk::Chunk() {
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);
    }
    
    
    Chunk::~Chunk() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    bool Chunk::occluded(GLubyte x, GLubyte y, GLubyte z, CubeDirection direction) const {
        static constexpr GLubyte MAX_X = X - 1;
        static constexpr GLubyte MAX_Y = Y - 1;
        static constexpr GLubyte MAX_Z = Z - 1;
        
        switch (direction) {
            case CubeDirection::FACE:
                return z < MAX_Z && this->cubes[x][y][z + 1] != CubeType::AIR;
            case CubeDirection::TOP:
                return y < MAX_Y && this->cubes[x][y + 1][z] != CubeType::AIR;
            case CubeDirection::BACK:
                return z > 0 && this->cubes[x][y][z - 1] != CubeType::AIR;
            case CubeDirection::BOTTOM:
                return y > 0 && this->cubes[x][y - 1][z] != CubeType::AIR;
            case CubeDirection::LEFT:
                return x > 0 && this->cubes[x - 1][y][z] != CubeType::AIR;
            case CubeDirection::RIGHT:
                return x < MAX_X && this->cubes[x + 1][y][z] != CubeType::AIR;
        }
    }
    
    
    CubeType Chunk::get(GLubyte x, GLubyte y, GLubyte z) {
        assert(x < X);
        assert(y < Y);
        assert(z < Z);
        
        return this->cubes[x][y][z];
    }
    
    
    void Chunk::set(GLubyte x, GLubyte y, GLubyte z, CubeType type) {
        assert(x < X);
        assert(y < Y);
        assert(z < Z);
        
        this->cubes[x][y][z] = type;
        this->modified = true;
    }
    
    
    GLuint Chunk::update() {
        if (!modified) {
            return this->count;
        }
        
        CubeType type;
        CubeFace drawn[SIZE];
        
        this->count = 0;
        for (GLubyte x = 0; x < X; x++) {
            for (GLubyte y = 0; y < Y; y++) {
                for (GLubyte z = 0; z < Z; z++) {
                    type = this->cubes[x][y][z];
                    if (type != CubeType::AIR) {
                        if (!occluded(x, y, z, CubeDirection::FACE)) {
                            drawn[this->count++] = CubeFace::face(x, y, z, type);
                        }
                        if (!occluded(x, y, z, CubeDirection::TOP)) {
                            drawn[this->count++] = CubeFace::top(x, y, z, type);
                        }
                        if (!occluded(x, y, z, CubeDirection::BACK)) {
                            drawn[this->count++] = CubeFace::back(x, y, z, type);
                        }
                        if (!occluded(x, y, z, CubeDirection::BOTTOM)) {
                            drawn[this->count++] = CubeFace::bottom(x, y, z, type);
                        }
                        if (!occluded(x, y, z, CubeDirection::LEFT)) {
                            drawn[this->count++] = CubeFace::left(x, y, z, type);
                        }
                        if (!occluded(x, y, z, CubeDirection::RIGHT)) {
                            drawn[this->count++] = CubeFace::right(x, y, z, type);
                        }
                    }
                }
            }
        }
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeFace) * this->count, drawn, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vao);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glEnableVertexAttribArray(VERTEX_ATTR_TYPE);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glVertexAttribPointer(
            VERTEX_ATTR_POSITION, 3, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            (const GLvoid *) (offsetof(cube::CubeVertex, vertex))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, 3, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            (const GLvoid *) (offsetof(cube::CubeVertex, normal))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_TEXTURE, 2, GL_BYTE, GL_FALSE, sizeof(cube::CubeVertex),
            (const GLvoid *) (offsetof(cube::CubeVertex, texture))
        );
        glVertexAttribIPointer(
            VERTEX_ATTR_TYPE, 1, GL_BYTE, sizeof(cube::CubeVertex),
            (const GLvoid *) (offsetof(cube::CubeVertex, type))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        this->modified = false;
        return this->count;
    }
    
    
    GLuint Chunk::render() {
        assert(!modified);
        
        if (this->count == 0) {
            return 0;
        }
        
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, this->count * CubeFace::VERTICE_COUNT);
        glBindVertexArray(0);
        
        return this->count;
    }
}
