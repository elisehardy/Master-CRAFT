#ifndef MASTERCRAFT_CHUNKMANAGER_HPP
#define MASTERCRAFT_CHUNKMANAGER_HPP

#include <vector>
#include <memory>
#include <unordered_map>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/util/SimplexNoise.hpp>
#include <mastercraft/cube/SuperChunk.hpp>
#include <mastercraft/entity/IEntity.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>


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
            std::vector<std::unique_ptr<entity::IEntity>> entities;
            util::SimplexNoise moistureSimplex;
            util::SimplexNoise heightSimplex;
            shader::Texture cubeTexture;
            GLubyte distanceView;  /**< Current distanceView. */
            GLuint textureVerticalOffset;
            GLuint tick;
            
            [[nodiscard]] glm::ivec3 getSuperChunkCoordinates(const glm::vec3 &position);
            
            [[nodiscard]] std::vector<glm::ivec3> generateKeys();
            
            [[nodiscard]] cube::CubeType getBiome(GLubyte height, GLubyte moisture);
            
            [[nodiscard]] cube::SuperChunk *createSuperChunk(glm::ivec3 position);
            
            [[nodiscard]] cube::SuperChunk *createSuperChunk(GLuint x, GLuint y, GLuint z);
            
            [[nodiscard]] entity::IEntity *createEntity(glm::ivec3 position);
            
            [[nodiscard]] entity::IEntity *createEntity(GLuint x, GLuint y, GLuint z);
        
        public:
            
            ChunkManager(const util::Image *t_cubeTexture, GLubyte distanceView);
            
            void updateDistanceView(GLubyte distance);
            
            void update();
            
            void render();
    };
}

#endif // MASTERCRAFT_CHUNKMANAGER_HPP
