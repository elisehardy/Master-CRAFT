#ifndef MASTERCRAFT_CHUNKMANAGER_HPP
#define MASTERCRAFT_CHUNKMANAGER_HPP

#include <vector>
#include <memory>
#include <unordered_map>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/util/SimplexNoise.hpp>
#include <mastercraft/cube/SuperChunk.hpp>


namespace mastercraft::game {
    
    struct Ivec3Hash {
        size_t operator()(const glm::ivec3 &k) const {
            return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
        }
        
        
        bool operator()(const glm::ivec3 &a, const glm::ivec3 &b) const {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }
    };
    
    
    
    class ChunkManager : public util::INonCopyable {
        
        private:
            std::unordered_map<glm::ivec3, std::unique_ptr<cube::SuperChunk>, Ivec3Hash, Ivec3Hash> chunks;
            util::SimplexNoise moistureSimplex;
            util::SimplexNoise heightSimplex;
            GLubyte distanceView;  /**< Current distanceView. */
        
            [[nodiscard]] std::vector<glm::ivec3> generateKeys();
            
            [[nodiscard]] cube::CubeType getBiome(GLubyte height, GLubyte moisture);
        
            [[nodiscard]] cube::SuperChunk *loadOrCreate(glm::ivec3 position);
            
            [[nodiscard]] cube::SuperChunk *loadOrCreate(GLuint x, GLuint y, GLuint z);
        
        public:
        
            ChunkManager() = default;
        
            void updateDrawDistance(GLubyte distance);
        
            void update();
            
            void render();
    };
}

#endif // MASTERCRAFT_CHUNKMANAGER_HPP