#include <algorithm>
#include <iostream>

#include <effolkronium/random.hpp>

#include <mastercraft/game/ChunkManager.hpp>
#include <mastercraft/game/Game.hpp>
#include <mastercraft/entity/Slime.hpp>
#include <glm/ext.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::game {
    
    ChunkManager::ChunkManager(const util::Image *t_cubeTexture, GLubyte t_distanceView) :
        cubeTexture(shader::Texture(t_cubeTexture)), distanceView(t_distanceView), textureVerticalOffset(0), tick(0) {
    }
    
    
    glm::ivec3 ChunkManager::getSuperChunkCoordinates(const glm::vec3 &position) {
        return glm::ivec3(
            std::floor(position.x / cube::SuperChunk::X) * cube::SuperChunk::X,
            std::floor(position.y / cube::SuperChunk::Y) * cube::SuperChunk::Y,
            std::floor(position.z / cube::SuperChunk::Z) * cube::SuperChunk::Z
        );
    }
    
    
    std::vector<glm::ivec3> ChunkManager::generateKeys() {
        glm::vec3 camera = Game::getInstance()->camera->getPosition();
        glm::ivec3 position = getSuperChunkCoordinates(camera);
        
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
        static constexpr GLubyte dirtLevel = sandLevel + 12;
        static constexpr GLubyte stoneLevel = dirtLevel + 4;
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
    
    
    cube::SuperChunk *ChunkManager::createSuperChunk(glm::ivec3 position) {
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
    
    
    cube::SuperChunk *ChunkManager::createSuperChunk(GLuint x, GLuint y, GLuint z) {
        return createSuperChunk({ x, y, z });
    }
    
    
    entity::IEntity *ChunkManager::createEntity(glm::ivec3 position) {
        GLint x = Random::get<GLint>(position.x, position.x + cube::SuperChunk::X);
        GLint z = Random::get<GLint>(position.z, position.z + cube::SuperChunk::Z);
        
        return new entity::Slime(x, 100, z);
    }
    
    
    entity::IEntity *ChunkManager::createEntity(GLuint x, GLuint y, GLuint z) {
        return createEntity({ x, y, z });
    }
    
    
    void ChunkManager::updateDistanceView(GLubyte distance) {
        this->distanceView = distance;
    }
    
    
    void ChunkManager::update() {
        if (++this->tick >= 4) {
            this->textureVerticalOffset = (this->textureVerticalOffset + 1) % 64;
            this->tick = 0;
        }
        
        auto keys = generateKeys();
        
        // Delete superChunk outside distanceView
        std::vector<glm::ivec3> toErase;
        for (const auto &entry : this->chunks) {
            if (!std::count(keys.begin(), keys.end(), entry.first)) {
                toErase.push_back(entry.first);
            }
        }
        for (const auto &key : toErase) {
            this->chunks.erase(key);
        }
        
        // Add new superChunk that entered distanceView and update every superChunk
        for (const auto &key : keys) {
            if (!this->chunks.count(key)) {
                this->chunks.emplace(key, this->createSuperChunk(key));
                this->entities.emplace_back(this->createEntity(key));
            }
            this->chunks[key]->update();
        }
        
        // Delete entity on superChunk outside distanceView
        std::vector<GLuint> toErase2;
        for (GLuint i = 0; i < this->entities.size(); i++) {
            const auto &key = getSuperChunkCoordinates(this->entities[i]->getPosition());
            if (!this->chunks.count(key)) {
                toErase2.push_back(i - toErase2.size());
            }
        }
        for (const auto &index : toErase2) {
            this->entities.erase(this->entities.begin() + index);
        }
        
        // Update entities
        for (const auto &entity : this->entities) {
            entity->update();
        }
    }
    
    
    void ChunkManager::render() {
        Game *game = Game::getInstance();
        glm::mat4 globalMVMatrix = game->camera->getViewMatrix();
        
        game->shaderManager->cubeShader->use();
        game->shaderManager->cubeShader->loadUniform("uTextureVerticalOffset", &this->textureVerticalOffset);
        game->shaderManager->cubeShader->loadUniform("uMV", glm::value_ptr(globalMVMatrix));
        game->shaderManager->cubeShader
            ->loadUniform("uMVP", glm::value_ptr(game->camera->getProjMatrix() * globalMVMatrix));
        game->shaderManager->cubeShader
            ->loadUniform("uNormal", glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
        game->shaderManager->cubeShader->bindTexture(this->cubeTexture);
        for (auto &entry : this->chunks) {
            entry.second->render();
        }
        game->shaderManager->cubeShader->unbindTexture();
        
        game->shaderManager->entityShader->use();
        game->shaderManager->entityShader->loadUniform("uMV", glm::value_ptr(globalMVMatrix));
        game->shaderManager->entityShader
            ->loadUniform("uMVP", glm::value_ptr(game->camera->getProjMatrix() * globalMVMatrix));
        game->shaderManager->entityShader
            ->loadUniform("uNormal", glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
        for (const auto &entity : this->entities) {
            entity->render();
        }
    }
}
