#include <algorithm>
#include <iostream>

#include <effolkronium/random.hpp>

#include <mastercraft/game/ChunkManager.hpp>
#include <mastercraft/game/Game.hpp>
#include <mastercraft/entity/Slime.hpp>
#include <glm/ext.hpp>
#include <mastercraft/cube/ColumnGenerator.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::game {
    
    ChunkManager::ChunkManager(const util::Image *t_cubeTexture, GLubyte t_distanceView) :
        textureVerticalOffset(0), distanceView(t_distanceView), tick(0), cubeTexture(shader::Texture(t_cubeTexture)) {
    }
    
    
    glm::ivec3 ChunkManager::getSuperChunkCoordinates(const glm::vec3 &position) const {
        return glm::ivec3(
            std::floor(position.x / cube::SuperChunk::X) * cube::SuperChunk::X,
            std::floor(position.y / cube::SuperChunk::Y) * cube::SuperChunk::Y,
            std::floor(position.z / cube::SuperChunk::Z) * cube::SuperChunk::Z
        );
    }
    
    
    void ChunkManager::generateKeys() {
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
        
        this->keys = keys;
    }
    
    
    cube::CubeType ChunkManager::getBiome(GLubyte height) {
        assert(height >= ConfigManager::GEN_MIN_HEIGHT);
        assert(height <= ConfigManager::GEN_MAX_HEIGHT);
        
        static constexpr GLubyte sandLevel = ConfigManager::GEN_WATER_LEVEL + 3;
        static constexpr GLubyte dirtLevel = sandLevel + 15;
        static constexpr GLubyte stoneLevel = dirtLevel + 5;
        if (height <= ConfigManager::GEN_WATER_LEVEL) {
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
        GLubyte height;
        cube::CubeType biome;
        
        for (GLuint x = 0; x < cube::SuperChunk::X; x++) {
            for (GLuint z = 0; z < cube::SuperChunk::Z; z++) {
                height = this->heightSimplex(
                    position.x + GLint(x), position.z + GLint(z), ConfigManager::GEN_MIN_HEIGHT,
                    ConfigManager::GEN_MAX_HEIGHT
                );
                biome = ChunkManager::getBiome(height);
                auto column = cube::ColumnGenerator::generateColumn(height, biome);
                for (GLuint y = 0; y < cube::SuperChunk::Y; y++) {
                    chunk->set(x, y, z, column[y]);
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
    

        std::vector<glm::ivec3> ChunkManager::getKeys() const {
            return this->keys;
        }


        cube::CubeType ChunkManager::get(GLint x, GLint y, GLint z) const {
            glm::ivec3 superChunk = this->getSuperChunkCoordinates({x, y, z});
            
            if (this->chunks.count(superChunk)) {
                return this->chunks.at(superChunk)->get(x - superChunk.x, y - superChunk.y, z - superChunk.z);
            }
            return cube::CubeType::DIRT;
        }
    
    
    void ChunkManager::init() {
        this->cubeShader = std::make_unique<shader::ShaderTexture>(
            "../shader/cube.vs.glsl", "../shader/cube.fs.glsl"
        );
        this->cubeShader->addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
        this->cubeShader->addUniform("uChunkPosition", shader::UNIFORM_3_F);
        this->cubeShader->addUniform("uVerticalOffset", shader::UNIFORM_1_I);
        
        this->entityShader = std::make_unique<shader::ShaderTexture>(
            "../shader/entity.vs.glsl", "../shader/entity.fs.glsl"
        );
        this->entityShader->addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->entityShader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->entityShader->addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
    }
    
    
    void ChunkManager::update() {
        if (++this->tick >= 2) {
            this->textureVerticalOffset = (this->textureVerticalOffset + 1) % 64;
            this->tick = 0;
        }
        
        generateKeys();
        
        // Delete superChunk outside distanceView
        std::vector<glm::ivec3> toErase;
        for (const auto &entry : this->chunks) {
            if (!std::count(this->keys.begin(), this->keys.end(), entry.first)) {
                toErase.push_back(entry.first);
            }
        }
        for (const auto &key : toErase) {
            this->chunks.erase(key);
        }
        
        // Add new superChunk that entered distanceView
        for (const auto &key : this->keys) {
            if (!this->chunks.count(key)) {
                this->chunks.emplace(key, this->createSuperChunk(key));
                this->entities.emplace_back(this->createEntity(key));
            }
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
        
        // Update superChunks
        for (const auto &key : this->keys) {
            this->chunks[key]->update();
        }
        // Update entities
        for (const auto &entity : this->entities) {
            entity->update();
        }
    }
    
    
    void ChunkManager::render() {
        Game *game = Game::getInstance();
        glm::mat4 MVMatrix = game->camera->getViewMatrix();
        glm::mat4 MVPMatrix = game->camera->getProjMatrix() * MVMatrix;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(MVMatrix));
        
        this->cubeShader->use();
        this->cubeShader->loadUniform("uMV", glm::value_ptr(MVMatrix));
        this->cubeShader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        this->cubeShader->loadUniform("uNormal", glm::value_ptr(normalMatrix));
        this->cubeShader->loadUniform("uVerticalOffset", &this->textureVerticalOffset);
        this->cubeShader->bindTexture(this->cubeTexture);
        std::for_each(this->chunks.begin(), this->chunks.end(), [](const auto &entry){ entry.second->render(false);});
        std::for_each(this->chunks.begin(), this->chunks.end(), [](const auto &entry){ entry.second->render(true);});
        this->cubeShader->unbindTexture();
        this->cubeShader->stop();
        
        this->entityShader->use();
        this->entityShader->loadUniform("uMV", glm::value_ptr(MVMatrix));
        this->entityShader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        this->entityShader->loadUniform("uNormal", glm::value_ptr(normalMatrix));
        for (const auto &entity : this->entities) {
            entity->render();
        }
        this->entityShader->stop();
    }
}
