#ifndef MASTERCRAFT_SUPERCHUNK_HPP
#define MASTERCRAFT_SUPERCHUNK_HPP

#include <glm/glm.hpp>

#include <mastercraft/cube/Chunk.hpp>
#include <mastercraft/shader/Shader.hpp>
#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/game/ConfigManager.hpp>


namespace mastercraft::cube {
    
    class SuperChunk : public util::INonCopyable {
        public:
            static constexpr GLubyte CHUNK_X = 1;
            static constexpr GLubyte CHUNK_Y = 8;
            static constexpr GLubyte CHUNK_Z = 1;
            static constexpr GLuint CHUNK_SIZE = CHUNK_X * CHUNK_Y * CHUNK_Z;
            static constexpr GLuint X = Chunk::X * CHUNK_X;
            static constexpr GLuint Y = Chunk::Y * CHUNK_Y;
            static constexpr GLuint Z = Chunk::Z * CHUNK_Z;
            static constexpr GLuint SIZE = CHUNK_SIZE * Chunk::SIZE;
            
            static_assert(game::ConfigManager::GEN_MAX_HEIGHT < Y);
        
        private:
            Chunk chunks[CHUNK_X][CHUNK_Y][CHUNK_Z];
            glm::ivec3 position;
            GLboolean modified;
            GLuint count;
        
        public:
            
            SuperChunk() = default;
            
            explicit SuperChunk(glm::ivec3 position);
            
            SuperChunk(GLuint x, GLuint y, GLuint z);
            
            ~SuperChunk() = default;
            
            CubeType get(GLuint x, GLuint y, GLuint z);
            
            void set(GLuint x, GLuint y, GLuint z, CubeType type);
            
            GLuint update();
            
            GLuint render();
    };
}

#endif //MASTERCRAFT_SUPERCHUNK_HPP
