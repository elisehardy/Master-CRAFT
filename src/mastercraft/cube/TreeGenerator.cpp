#include <stdexcept>

#include <effolkronium/random.hpp>

#include <mastercraft/cube/TreeGenerator.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::cube {
    
    TreeGenerator::Tree TreeGenerator::plainTree(glm::vec3 position) {
        return mastercraft::cube::TreeGenerator::Tree();
    }
    
    
    TreeGenerator::Tree TreeGenerator::jungleTree(glm::vec3 position) {
        return mastercraft::cube::TreeGenerator::Tree();
    }
    
    
    TreeGenerator::Tree TreeGenerator::snowTree(glm::vec3 position) {
        return mastercraft::cube::TreeGenerator::Tree();
    }
    
    
    TreeGenerator::Tree TreeGenerator::cactus(glm::vec3 position) {
        uint32_t limit = Random::get(2u, 5u);
        Tree tree;
        
        for (uint32_t i = 0; i < limit; i++) {
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i, position.z), CubeType::CACTUS);
        }
        
        return tree;
    }
    
    
    TreeGenerator::Tree TreeGenerator::generate(glm::ivec3 position, CubeType biome) {
        switch (biome) {
            case DIRT_PLAIN:
                if (Random::get<bool>(0.005)) {
                    return plainTree(position);
                }
                break;
            case DIRT_JUNGLE:
                if (Random::get<bool>(0.05)) {
                    return jungleTree(position);
                }
                break;
            case DIRT_SNOW:
                if (Random::get<bool>(0.005)) {
                    return snowTree(position);
                }
                break;
            case SAND_DESERT:
                if (Random::get<bool>(0.005)) {
                    return cactus(position);
                }
                break;
            case AIR:
            case WATER:
            case SAND_BEACH:
            case ICE:
            case SNOW:
            case STONE:
            case STONE_SNOW:
            case FLOWERS:
            case WOOD_PLAIN:
            case WOOD_JUNGLE:
            case WOOD_SNOW:
            case CACTUS:
            case LEAVES_PLAIN:
            case LEAVES_JUNGLE:
            case LEAVES_SNOW:
                break;
        }
        
        return {};
    }
}
