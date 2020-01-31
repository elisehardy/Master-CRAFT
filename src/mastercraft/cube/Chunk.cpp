#include <iostream>

#include <mastercraft/cube/Chunk.hpp>
#include <mastercraft/cube/CubeFace.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::cube {
    
    Chunk::Chunk() {
        glGenBuffers(1, &this->vboAlpha);
        glGenVertexArrays(1, &this->vaoAlpha);
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }
    
    
    Chunk::~Chunk() {
        glDeleteBuffers(1, &this->vboAlpha);
        glDeleteVertexArrays(1, &this->vaoAlpha);
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    bool Chunk::onBorder(GLubyte x, GLubyte y, GLubyte z) {
        static constexpr GLubyte MAX_X = X - 1;
        static constexpr GLubyte MAX_Y = Y - 1;
        static constexpr GLubyte MAX_Z = Z - 1;
        
        return x == MAX_X || y == MAX_Y || z == MAX_Z || !x || !y || !z;
    }
    
    
    bool Chunk::occluded(CubeType type, GLint x, GLint y, GLint z, CubeDirection direction) const {
        if (onBorder(x, y, z)) {
            game::Game *game = game::Game::getInstance();
            
            x += this->position.x;
            y += this->position.y;
            z += this->position.z;
            
            if (type == CubeType::WATER) {
                switch (direction) {
                    case CubeDirection::FACE:
                        return game->chunkManager->get(x, y, z + 1) != CubeType::AIR;
                    case CubeDirection::TOP:
                        return game->chunkManager->get(x, y + 1, z) != CubeType::AIR;
                    case CubeDirection::BACK:
                        return game->chunkManager->get(x, y, z - 1) != CubeType::AIR;
                    case CubeDirection::BOTTOM:
                        return game->chunkManager->get(x, y - 1, z) != CubeType::AIR;
                    case CubeDirection::LEFT:
                        return game->chunkManager->get(x - 1, y, z) != CubeType::AIR;
                    case CubeDirection::RIGHT:
                        return game->chunkManager->get(x + 1, y, z) != CubeType::AIR;
                }
            }
            
            switch (direction) {
                case CubeDirection::FACE:
                    return !(game->chunkManager->get(x, y, z + 1) & TRANSPARENT);
                case CubeDirection::TOP:
                    return !(game->chunkManager->get(x, y + 1, z) & TRANSPARENT);
                case CubeDirection::BACK:
                    return !(game->chunkManager->get(x, y, z - 1) & TRANSPARENT);
                case CubeDirection::BOTTOM:
                    return !(game->chunkManager->get(x, y - 1, z) & TRANSPARENT);
                case CubeDirection::LEFT:
                    return !(game->chunkManager->get(x - 1, y, z) & TRANSPARENT);
                case CubeDirection::RIGHT:
                    return !(game->chunkManager->get(x + 1, y, z) & TRANSPARENT);
            }
        }
        
        if (type == CubeType::WATER) {
            switch (direction) {
                case CubeDirection::FACE:
                    return this->cubes[x][y][z + 1] != CubeType::AIR;
                case CubeDirection::TOP:
                    return this->cubes[x][y + 1][z] != CubeType::AIR;
                case CubeDirection::BACK:
                    return this->cubes[x][y][z - 1] != CubeType::AIR;
                case CubeDirection::BOTTOM:
                    return this->cubes[x][y - 1][z] != CubeType::AIR;
                case CubeDirection::LEFT:
                    return this->cubes[x - 1][y][z] != CubeType::AIR;
                case CubeDirection::RIGHT:
                    return this->cubes[x + 1][y][z] != CubeType::AIR;
            }
        }
        
        switch (direction) {
            case CubeDirection::FACE:
                return !(this->cubes[x][y][z + 1] & TRANSPARENT);
            case CubeDirection::TOP:
                return !(this->cubes[x][y + 1][z] & TRANSPARENT);
            case CubeDirection::BACK:
                return !(this->cubes[x][y][z - 1] & TRANSPARENT);
            case CubeDirection::BOTTOM:
                return !(this->cubes[x][y - 1][z] & TRANSPARENT);
            case CubeDirection::LEFT:
                return !(this->cubes[x - 1][y][z] & TRANSPARENT);
            case CubeDirection::RIGHT:
                return !(this->cubes[x + 1][y][z] & TRANSPARENT);
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
    
    
    void Chunk::setPosition(const glm::ivec3 &position) {
        this->position = position;
    }
    
    
    void Chunk::setPosition(GLint x, GLint y, GLint z) {
        this->position = { x, y, z };
    }
    
    
    GLuint Chunk::update() {
        static constexpr GLint FACE_COUNT = SIZE * 6;
        
        if (!modified) {
            return this->count;
        }
        
        this->countAlpha = 0;
        this->count = 0;
        
        CubeFace drawnAlpha[FACE_COUNT], drawn[FACE_COUNT];
        CubeType type;
        for (GLubyte x = 0; x < X; x++) {
            for (GLubyte y = 0; y < Y; y++) {
                for (GLubyte z = 0; z < Z; z++) {
                    type = this->cubes[x][y][z];
                    
                    if (type == CubeType::AIR) {
                        continue;
                    }
                    
                    if (type & TRANSPARENT) {
                        if (!occluded(type, x, y, z, CubeDirection::FACE)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::face(x, y, z, type | CubeDirection::FACE);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::TOP)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::top(x, y, z, type | CubeDirection::TOP);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::BACK)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::back(x, y, z, type | CubeDirection::BACK);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::BOTTOM)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::bottom(x, y, z, type | CubeDirection::BOTTOM);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::LEFT)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::left(x, y, z, type | CubeDirection::LEFT);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::RIGHT)) {
                            drawnAlpha[this->countAlpha++] = CubeFace::right(x, y, z, type | CubeDirection::RIGHT);
                        }
                    }
                    else {
                        if (!occluded(type, x, y, z, CubeDirection::FACE)) {
                            drawn[this->count++] = CubeFace::face(x, y, z, type | CubeDirection::FACE);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::TOP)) {
                            drawn[this->count++] = CubeFace::top(x, y, z, type | CubeDirection::TOP);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::BACK)) {
                            drawn[this->count++] = CubeFace::back(x, y, z, type | CubeDirection::BACK);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::BOTTOM)) {
                            drawn[this->count++] = CubeFace::bottom(x, y, z, type | CubeDirection::BOTTOM);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::LEFT)) {
                            drawn[this->count++] = CubeFace::left(x, y, z, type | CubeDirection::LEFT);
                        }
                        if (!occluded(type, x, y, z, CubeDirection::RIGHT)) {
                            drawn[this->count++] = CubeFace::right(x, y, z, type | CubeDirection::RIGHT);
                        }
                    }
                }
            }
        }
        
        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vboAlpha);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeFace) * this->countAlpha, drawnAlpha, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeFace) * this->count, drawn, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Set the VAO
        glBindVertexArray(this->vaoAlpha);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboAlpha);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glEnableVertexAttribArray(VERTEX_ATTR_DATA);
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
            VERTEX_ATTR_DATA, 1, GL_BYTE, sizeof(cube::CubeVertex),
            (const GLvoid *) (offsetof(cube::CubeVertex, data))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glEnableVertexAttribArray(VERTEX_ATTR_DATA);
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
            VERTEX_ATTR_DATA, 1, GL_BYTE, sizeof(cube::CubeVertex),
            (const GLvoid *) (offsetof(cube::CubeVertex, data))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        this->modified = false;
        return this->count + this->countAlpha;
    }
    
    
    GLuint Chunk::render(bool alpha) {
        assert(!modified);
        
        if (this->count + this->countAlpha == 0) {
            return 0;
        }
        
        if (!alpha) {
            glBindVertexArray(this->vao);
            glDrawArrays(GL_TRIANGLES, 0, this->count * CubeFace::VERTICE_COUNT);
            glBindVertexArray(0);
        }
        else {
            glBindVertexArray(this->vaoAlpha);
            glDrawArrays(GL_TRIANGLES, 0, this->countAlpha * CubeFace::VERTICE_COUNT);
            glBindVertexArray(0);
        }
        
        return this->count + this->countAlpha;
    }
}
