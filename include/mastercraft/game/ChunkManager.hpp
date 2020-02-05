#ifndef MASTERCRAFT_CHUNKMANAGER_HPP
#define MASTERCRAFT_CHUNKMANAGER_HPP

#include <vector>
#include <memory>
#include <map>

#include <glm/gtc/noise.hpp>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/cube/SuperChunk.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/util/Noise.hpp>
#include <mastercraft/entity/Slime.hpp>


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
        
        private:
            std::map<glm::ivec3, std::unique_ptr<cube::SuperChunk>, Ivec3Less> chunks;
            std::vector<std::unique_ptr<entity::Slime>> slimes;
            std::vector<glm::ivec3> keys;
            GLuint textureVerticalOffset;
            GLubyte distanceView;
            Noise2D temperatureNoise;
            Noise3D carvingNoise;
        
        public:
            std::unique_ptr<shader::ShaderTexture> entityShader;
            std::unique_ptr<shader::ShaderTexture> cubeShader;
            shader::Texture cubeTexture;
            Noise2D heightNoise;
        
        private:
            
            void generateKeys();
            
            [[nodiscard]] static cube::CubeType getBiome(GLuint height, GLfloat temperature);
            
            [[nodiscard]] glm::ivec3 getSuperChunkCoordinates(const glm::ivec3 &position) const;
            
            [[nodiscard]] cube::SuperChunk *createSuperChunk(glm::ivec3 position);
        
        public:
            
            ChunkManager(const util::Image *t_cubeTexture, GLubyte distanceView);
            
            void updateDistanceView(GLubyte distance);
            
            [[nodiscard]] cube::CubeType get(glm::ivec3 position) const;
            
            void init();
            
            void update();
            
            void render();
    };
}

#endif // MASTERCRAFT_CHUNKMANAGER_HPP
