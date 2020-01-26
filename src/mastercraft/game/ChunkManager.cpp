#include <algorithm>

#include <mastercraft/game/ChunkManager.hpp>
#include <mastercraft/game/Game.hpp>
#include <iostream>


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
                this->chunks.emplace(key, cube::SuperChunk::loadOrCreate(key));
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
