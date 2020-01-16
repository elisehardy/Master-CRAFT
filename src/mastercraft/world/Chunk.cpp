#include <mastercraft/world/Chunk.hpp>
#include <mastercraft/world/Cube.hpp>
#include <iostream>


namespace mastercraft::world {
    
    Chunk::Chunk() {
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);
    }
    
    
    Chunk::~Chunk() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    bool Chunk::occluded(GLubyte x, GLubyte y, GLubyte z) const {
        static constexpr GLubyte MAX_X = X - 1;
        static constexpr GLubyte MAX_Y = Y - 1;
        static constexpr GLubyte MAX_Z = Z - 1;
        
        return (
            (x > 0) && (x < MAX_X) && (y > 0) && (y < MAX_Y) && (z > 0) && (z < MAX_Z)
            && (this->cubes[x + 1][y][z] != CubeType::AIR) && (this->cubes[x - 1][y][z] != CubeType::AIR)
            && (this->cubes[x][y + 1][z] != CubeType::AIR) && (this->cubes[x][y - 1][z] != CubeType::AIR)
            && (this->cubes[x][y][z + 1] != CubeType::AIR) && (this->cubes[x][y][z - 1] != CubeType::AIR)
        );
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
        Cube drawn[SIZE];
        
        this->count = 0;
        for (GLubyte x = 0; x < X; x++) {
            for (GLubyte y = 0; y < Y; y++) {
                for (GLubyte z = 0; z < Z; z++) {
                    type = this->cubes[x][y][z];
                    if (type != CubeType::AIR && !this->occluded(x, y, z)) {
                        drawn[this->count++] = Cube(x, y, z, type);
                    }
                }
            }
        }
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Cube) * this->count, drawn, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vao);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glEnableVertexAttribArray(VERTEX_ATTR_TYPE);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glVertexAttribPointer(
            VERTEX_ATTR_POSITION, 3, GL_BYTE, GL_FALSE, sizeof(world::CubeVertex),
            (const GLvoid *) (offsetof(world::CubeVertex, vertex))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, 3, GL_BYTE, GL_FALSE, sizeof(world::CubeVertex),
            (const GLvoid *) (offsetof(world::CubeVertex, normal))
        );
        glVertexAttribPointer(
            VERTEX_ATTR_TEXTURE, 2, GL_BYTE, GL_FALSE, sizeof(world::CubeVertex),
            (const GLvoid *) (offsetof(world::CubeVertex, texture))
        );
        glVertexAttribIPointer(
            VERTEX_ATTR_TYPE, 1, GL_BYTE, sizeof(world::CubeVertex),
            (const GLvoid *) (offsetof(world::CubeVertex, type))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        this->modified = false;
        return this->count;
    }
    
    
    GLuint Chunk::draw() {
        assert(!modified);
        
        if (this->count == 0) {
            return 0;
        }
        
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, this->count * Cube::VERTICE_COUNT);
        glBindVertexArray(0);
        
        return this->count;
    }
}
