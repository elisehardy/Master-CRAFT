#include <algorithm>
#include <iostream>

#include <mastercraft/game/ChunkManager.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    std::vector<glm::ivec3> ChunkManager::generateKeys() {
        glm::vec3 camera = Game::getInstance()->camera->getPosition();
        glm::ivec3 position = glm::ivec3(
            std::floor(camera.x / cube::SuperChunk::X) * cube::SuperChunk::X,
            std::floor(camera.y / cube::SuperChunk::Y) * cube::SuperChunk::Y,
            std::floor(camera.z / cube::SuperChunk::Z) * cube::SuperChunk::Z
        );
        
        GLint startx = position.x - distanceView * cube::SuperChunk::X;
        GLint startz = position.z - distanceView * cube::SuperChunk::Z;
        GLint endx = position.x + distanceView * cube::SuperChunk::X;
        GLint endz = position.z + distanceView * cube::SuperChunk::Z;
        std::vector<glm::ivec3> keys = std::vector<glm::ivec3>();
        for (GLint x = startx; x <= endx; x += cube::SuperChunk::X) {
            for (GLint z = startz; z <= endz; z += cube::SuperChunk::Z) {
                keys.emplace_back(x, 0, z);
            }
        }
        
        return keys;
    }
    
    
    cube::CubeType ChunkManager::getBiome(GLubyte height, GLubyte moisture) {
        assert(height >= ConfigManager::GEN_MIN_HEIGHT);
        assert(height <= ConfigManager::GEN_MAX_HEIGHT);
        
        static constexpr GLubyte waterLevel = ConfigManager::GEN_MIN_HEIGHT + 3;
        static constexpr GLubyte sandLevel = waterLevel + 4;
        static constexpr GLubyte stoneLevel = ConfigManager::GEN_MAX_HEIGHT - 5;
        static constexpr GLubyte dirtLevel = sandLevel + (stoneLevel - sandLevel) * 0.6;
        if (height <= waterLevel) {
            return cube::CubeType::WATER;
        }
        if (height <= sandLevel) {
            return cube::CubeType::SAND;
        }
        if (height <= dirtLevel) {
            return cube::CubeType::DIRT;
        }
        if (height <= stoneLevel) {
            return cube::CubeType::STONE;
        }
        return cube::CubeType::SNOW;
    }
    
    
    cube::SuperChunk *ChunkManager::loadOrCreate(glm::ivec3 position) {
        auto *chunk = new cube::SuperChunk(position);
        GLubyte height, moisture;
        cube::CubeType biome;
        
        for (GLuint x = 0; x < cube::SuperChunk::X; x++) {
            for (GLuint z = 0; z < cube::SuperChunk::Z; z++) {
                height = this->heightSimplex(
                    position.x + x, position.z + z, ConfigManager::GEN_MIN_HEIGHT, ConfigManager::GEN_MAX_HEIGHT
                );
//                moisture = this->heightSimplex(position.x + x, position.z + z, 0, 255);
                moisture = 0;
                biome = ChunkManager::getBiome(height, moisture);
                for (GLuint y = 0; y < cube::SuperChunk::Y; y++) {
                    if (y <= height) {
                        chunk->set(x, y, z, biome);
                    }
                    else {
                        chunk->set(x, y, z, cube::CubeType::AIR);
                    }
                }
            }
        }
        
        return chunk;
    }
    
    
    cube::SuperChunk *ChunkManager::loadOrCreate(GLuint x, GLuint y, GLuint z) {
        return loadOrCreate({ x, y, z });
    }
    
    
    void ChunkManager::updateDrawDistance(GLubyte distance) {
        this->distanceView = distance;
    }
    
    
    void ChunkManager::update() {
        auto keys = generateKeys();
        
        std::vector<glm::ivec3> toErase;
        for (const auto &entry : this->chunks) {
            if (!std::count(keys.begin(), keys.end(), entry.first)) {
                toErase.push_back(entry.first);
            }
        }
        for (const auto &key : toErase) {
            this->chunks.erase(key);
        }
        
        for (const auto &key : keys) {
            if (!this->chunks.count(key)) {
                this->chunks.emplace(key, ChunkManager::loadOrCreate(key));
            }
            this->chunks[key]->update();
        }
    }
    
    
    void ChunkManager::render() {
        for (auto &entry : this->chunks) {
            entry.second->render();
        }
    }
}
