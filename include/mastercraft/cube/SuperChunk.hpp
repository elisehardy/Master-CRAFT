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
            static constexpr GLint CHUNK_X = 2;
            static constexpr GLint CHUNK_Y = 16;
            static constexpr GLint CHUNK_Z = 2;
            static constexpr GLint CHUNK_SIZE = CHUNK_X * CHUNK_Y * CHUNK_Z;
            static constexpr GLint X = Chunk::X * CHUNK_X;
            static constexpr GLint Y = Chunk::Y * CHUNK_Y;
            static constexpr GLint Z = Chunk::Z * CHUNK_Z;
            static constexpr GLint SIZE = CHUNK_SIZE * Chunk::SIZE;
            
            static_assert(game::ConfigManager::GEN_MAX_HEIGHT <= Y);
        
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
            
            void touch();
            
            GLuint update();
            
            GLuint render(bool alpha);
    };
}

#endif //MASTERCRAFT_SUPERCHUNK_HPP
