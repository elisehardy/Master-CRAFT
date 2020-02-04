#ifndef MASTERCRAFT_CHUNKMANAGER_HPP
#define MASTERCRAFT_CHUNKMANAGER_HPP

#include <vector>
#include <memory>
#include <map>

#include <glm/gtc/noise.hpp>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/cube/SuperChunk.hpp>
#include <mastercraft/entity/IEntity.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/util/Noise.hpp>


namespace mastercraft::game {

    typedef util::Noise<glm::vec2, float, glm::simplex> Noise2D;
    typedef util::Noise<glm::vec3, float, glm::perlin> Noise3D;
    
    
    
    struct Ivec3Less {
        size_t operator()(const glm::ivec3 &v1, const glm::ivec3 &v2) const {
            if (v1.x == v2.x) {
                if (v1.y == v2.y) {
                    return v1.z < v2.z;
                }
                return v1.y < v2.y;
            }
            return v1.x < v2.x;

        }
    };


    class ChunkManager : public util::INonCopyable {
<<<<<<< HEAD
        
        private:
<<<<<<< HEAD
            std::map<glm::ivec3, std::unique_ptr<cube::SuperChunk>, Ivec3Less> chunks;
            std::vector<std::unique_ptr<entity::IEntity>> entities;
            std::vector<glm::ivec3> keys;
            GLuint textureVerticalOffset;
            GLubyte distanceView;
            Noise2D heightNoise;
            Noise2D moistureNoise;
            Noise3D carvingNoise;
        
        public:
            std::unique_ptr<shader::ShaderTexture> entityShader;
            std::unique_ptr<shader::ShaderTexture> cubeShader;
            shader::Texture cubeTexture;
=======
            std::unordered_map<glm::ivec3, std::unique_ptr<cube::SuperChunk>, Ivec3Hash, Ivec3Hash> chunks;
            util::SimplexNoise moistureSimplex;
            GLubyte distanceView;  /**< Current distanceView. */
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
        
        private:
            
            void generateKeys();
            
            [[nodiscard]] cube::CubeType getBiome(GLubyte height, GLubyte moisture);
<<<<<<< HEAD

            [[nodiscard]] glm::ivec3 getSuperChunkCoordinates(const glm::ivec3 &position) const;
            
            [[nodiscard]] glm::ivec3 getSuperChunkCoordinates(GLint x, GLint y, GLint z) const;
            

            [[nodiscard]] cube::SuperChunk *createSuperChunk(glm::ivec3 position);
            
            [[nodiscard]] cube::SuperChunk *createSuperChunk(GLint x, GLint y, GLint z);
            
            [[nodiscard]] entity::IEntity *createEntity(glm::ivec3 position);
        
        public:
            
            ChunkManager(const util::Image *t_cubeTexture, GLubyte distanceView);
            
            void updateDistanceView(GLubyte distance);
            
            [[nodiscard]] std::vector<glm::ivec3> getKeys() const;
            
            [[nodiscard]] cube::CubeType get(GLint x, GLint y, GLint z);
            
            void init();
            

=======
        
            [[nodiscard]] cube::SuperChunk *loadOrCreate(glm::ivec3 position);

    public:
        util::SimplexNoise heightSimplex;

        ChunkManager() = default;
        
            void updateDrawDistance(GLubyte distance);
        
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
            void update();
            
            void render();

<<<<<<< HEAD
    private:
        std::unordered_map<glm::ivec3, std::unique_ptr<cube::SuperChunk>, Ivec3Hash, Ivec3Hash> chunks;
        std::vector<std::unique_ptr<mastercraft::entity::IEntity>> entities;
        util::SimplexNoise moistureSimplex;
        shader::Texture cubeTexture;

        GLubyte distanceView;  /**< Current distanceView. */
        GLuint textureVerticalOffset;
        GLuint tick;

        [[nodiscard]] std::vector<glm::ivec3> generateKeys();

        [[nodiscard]] cube::CubeType getBiome(GLubyte height, GLubyte moisture);

        [[nodiscard]] cube::SuperChunk *createSuperChunk(glm::ivec3 position);

        [[nodiscard]] cube::SuperChunk *createSuperChunk(GLuint x, GLuint y, GLuint z);

        [[nodiscard]] entity::IEntity *createEntity(glm::ivec3 position);

        [[nodiscard]] entity::IEntity *createEntity(GLuint x, GLuint y, GLuint z);

    public:




=======
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
        [[nodiscard]] cube::SuperChunk *loadOrCreate(GLuint x, GLuint y, GLuint z);
    };
}

#endif // MASTERCRAFT_CHUNKMANAGER_HPP
