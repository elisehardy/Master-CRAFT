#include <algorithm>
#include <iostream>

#include <effolkronium/random.hpp>
#include <glm/ext.hpp>

#include <mastercraft/game/ChunkManager.hpp>
#include <mastercraft/game/Game.hpp>
#include <mastercraft/entity/Slime.hpp>
#include <mastercraft/cube/ColumnGenerator.hpp>
#include <mastercraft/cube/TreeGenerator.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::game {
    
    ChunkManager::ChunkManager(const util::Image *t_cubeTexture, GLubyte t_distanceView) :
        textureVerticalOffset(0), distanceView(t_distanceView),
        temperatureNoise(
            { Random::get<float>(0., 100000.), Random::get<float>(0., 100000.) }, 3, 1.f, 1 / 512.f, 0.5f, 2.f
        ),

        carvingNoise(
            { Random::get<float>(0., 100000.), Random::get<float>(0., 100000.), Random::get<float>(0., 100000.) },
            3, 1.f, 1 / 64.f, 0.5f, 2.f
        ),

        cubeTexture(shader::Texture(t_cubeTexture)),
        heightNoise({ Random::get<float>(0., 100000.), Random::get<float>(0., 100000.) }, 3, 1.f, 1 / 256.f, 0.5f, 2.f)
    {
    }
    
    
    glm::ivec3 ChunkManager::getSuperChunkCoordinates(const glm::ivec3 &position) const {
        return glm::ivec3(
            std::floor(position.x / cube::SuperChunk::X) * cube::SuperChunk::X,
            std::floor(position.y / cube::SuperChunk::Y) * cube::SuperChunk::Y,
            std::floor(position.z / cube::SuperChunk::Z) * cube::SuperChunk::Z
        );
    }
    
    
    glm::ivec3 ChunkManager::getSuperChunkCoordinates(GLint x, GLint y, GLint z) const {
        return getSuperChunkCoordinates({ x, y, z });
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
    
    
    cube::CubeType ChunkManager::getBiome(GLubyte height, float temperature) {
        assert(height >= ConfigManager::GEN_MIN_HEIGHT);
        assert(height <= ConfigManager::GEN_MAX_HEIGHT);
        
        static constexpr GLubyte sandLevel = ConfigManager::GEN_WATER_LEVEL + 3;
        static constexpr GLubyte dirtLevel = sandLevel + 18;
        static constexpr GLubyte stoneLevel = dirtLevel + 4;
        
        if (temperature < -0.30f) { // Snow biome
            if (height <= ConfigManager::GEN_WATER_LEVEL) {
                return cube::CubeType::ICE;
            }
            if (height <= sandLevel) {
                return cube::CubeType::SNOW;
            }
            if (height <= dirtLevel) {
                return cube::CubeType::DIRT_SNOW;
            }
            if (height <= stoneLevel) {
                return cube::CubeType::STONE_SNOW;
            }
            return cube::CubeType::SNOW;
        }
        else if (temperature < -0.125f || (temperature > 0.125f && temperature < 0.30f)) { // Plain biome
            if (height <= ConfigManager::GEN_WATER_LEVEL) {
                return cube::CubeType::WATER;
            }
            if (height <= sandLevel) {
                return cube::CubeType::SAND_BEACH;
            }
            if (height <= dirtLevel) {
                return cube::CubeType::DIRT_PLAIN;
            }
            if (height <= stoneLevel) {
                return cube::CubeType::STONE;
            }
            return cube::CubeType::STONE_SNOW;
        }
        else if (temperature < 0.125f) { // Jungle biome
            if (height <= ConfigManager::GEN_WATER_LEVEL) {
                return cube::CubeType::WATER;
            }
            if (height <= sandLevel) {
                return cube::CubeType::DIRT_JUNGLE;
            }
            if (height <= dirtLevel) {
                return cube::CubeType::DIRT_JUNGLE;
            }
            if (height <= stoneLevel) {
                return cube::CubeType::STONE;
            }
            return cube::CubeType::STONE;
        }
        // Desert biome
        if (height <= ConfigManager::GEN_WATER_LEVEL) {
            return cube::CubeType::WATER;
        }
        if (height <= sandLevel) {
            return cube::CubeType::SAND_BEACH;
        }
        if (height <= dirtLevel) {
            return cube::CubeType::SAND_DESERT;
        }
        if (height <= stoneLevel) {
            return cube::CubeType::SAND_DESERT;
        }
        return cube::CubeType::STONE;
    }
    
    
    cube::SuperChunk *ChunkManager::createSuperChunk(glm::ivec3 position) {
        auto *chunk = new cube::SuperChunk(position);
        cube::CubeType biome;
        float temperature;
        GLubyte height;
        
        for (GLuint x = 0; x < cube::SuperChunk::X; x++) {
            for (GLuint z = 0; z < cube::SuperChunk::Z; z++) {
                height = this->heightNoise(
                    { position.x + GLint(x), position.z + GLint(z) }, -1, 1, ConfigManager::GEN_MIN_HEIGHT,
                    ConfigManager::GEN_MAX_HEIGHT
                );
                for (GLuint y = 0; y <= height; y++) {
                    chunk->set(x, y, z, cube::CubeType::STONE);
                }
                for (GLuint y = height + 1; y < cube::SuperChunk::Y; y++) {
                    chunk->set(x, y, z, cube::CubeType::AIR);
                }
            }
        }
        
        //        glm::vec3 point;
        //        for (GLuint x = 0; x < cube::SuperChunk::X; x++) {
        //            for (GLuint y = ConfigManager::GEN_CARVING_HEIGHT; y < ConfigManager::GEN_MAX_HEIGHT; y++) {
        //                for (GLuint z = 0; z < cube::SuperChunk::Z; z++) {
        //                    point = { position.x + GLint(x), position.y + GLint(y), position.z + GLint(z) };
        //                    if (this->noise3D(point) > 0.f) {
        //                        chunk->set(x, y, z, cube::CubeType::AIR);
        //                    }
        //                }
        //            }
        //        }
        
        for (GLuint x = 0; x < cube::SuperChunk::X; x++) {
            for (GLuint z = 0; z < cube::SuperChunk::Z; z++) {
                for (GLuint y = ConfigManager::GEN_MAX_HEIGHT; y >= ConfigManager::GEN_MIN_HEIGHT; y--) {
                    if (chunk->get(x, y, z) != cube::CubeType::AIR) {
                        
                        temperature = this->temperatureNoise({ position.x + GLint(x), position.z + GLint(z) });
                        biome = ChunkManager::getBiome(y, temperature);
                        auto column = cube::ColumnGenerator::generate(y, biome);
                        for (GLuint y2 = ConfigManager::GEN_MIN_HEIGHT; y2 <= ConfigManager::GEN_MAX_HEIGHT; y2++) {
                            chunk->set(x, y2, z, column[y2]);
                        }
                        
                        auto tree = cube::TreeGenerator::generate({ x, y, z }, biome);
                        std::for_each(
                            tree.begin(), tree.end(),
                            [&chunk](const auto &e) { chunk->set(e.first.x, e.first.y, e.first.z, e.second); }
                        );
                        
                        break;
                    }
                }
            }
        }
        
        GLint startx = position.x - cube::SuperChunk::X;
        GLint startz = position.z - cube::SuperChunk::Z;
        GLint endx = position.x + cube::SuperChunk::X;
        GLint endz = position.z + cube::SuperChunk::Z;
        for (GLint x = startx; x <= endx; x += cube::SuperChunk::X) {
            for (GLint z = startz; z <= endz; z += cube::SuperChunk::Z) {
                if (this->chunks.count({ x, 0, z })) {
                    this->chunks.at({ x, 0, z })->touch();
                }
            }
        }
        return chunk;
    }
    
    
    cube::SuperChunk *ChunkManager::createSuperChunk(GLint x, GLint y, GLint z) {
        return createSuperChunk({ x, y, z });
    }
    
    
    entity::IEntity *ChunkManager::createEntity(glm::ivec3 position) {
        Game *game = Game::getInstance();

        GLint x = Random::get<GLint>(position.x, position.x + cube::SuperChunk::X);
        GLint z = Random::get<GLint>(position.z, position.z + cube::SuperChunk::Z);

        return new entity::Slime(x, game->chunkManager->heightNoise(glm::vec2(x,z),-1, 1, ConfigManager::GEN_MIN_HEIGHT,
                                                                    ConfigManager::GEN_MAX_HEIGHT)+1, z);
    }
    
    
    void ChunkManager::updateDistanceView(GLubyte distance) {
        this->distanceView = distance;
    }
    
    
    std::vector<glm::ivec3> ChunkManager::getKeys() const {
        return this->keys;
    }
    
    
    cube::CubeType ChunkManager::get(GLint x, GLint y, GLint z) {
        glm::ivec3 superChunk = this->getSuperChunkCoordinates({ x, y, z });
        
        if (this->chunks.count(superChunk)) {
            return this->chunks.at(superChunk)->get(x - superChunk.x, y - superChunk.y, z - superChunk.z);
        }
        
        return cube::CubeType::STONE;
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
        this->textureVerticalOffset = (this->textureVerticalOffset + 1) % 64;
        
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
        std::for_each(
            this->keys.begin(), this->keys.end(),
            [this](const auto &key) {
                if (!this->chunks.count(key)) {
                    this->chunks.emplace(key, this->createSuperChunk(key));
                    this->entities.emplace_back(this->createEntity(key));
                }
            }
        );
        
        // Update superChunks
        std::for_each(this->chunks.begin(), this->chunks.end(),
            [](const auto &entry) { entry.second->update(); }
        );

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
        std::for_each(this->chunks.begin(), this->chunks.end(),
            [](const auto &entry) { entry.second->render(false); }
        );
        glDisable(GL_CULL_FACE);
        std::for_each(this->chunks.begin(), this->chunks.end(),
            [](const auto &entry) { entry.second->render(true); }
        );
        glEnable(GL_CULL_FACE);
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
