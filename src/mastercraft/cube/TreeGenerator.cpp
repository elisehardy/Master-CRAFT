#include <stdexcept>

#include <effolkronium/random.hpp>

#include <mastercraft/cube/TreeGenerator.hpp>
#include <mastercraft/game/Game.hpp>
#include <iostream>


using Random = effolkronium::random_static;

namespace mastercraft::cube {
    
    TreeGenerator::Tree TreeGenerator::plainTree(glm::vec3 position) {
        if(position.x+6 >= Chunk::X || position.x-6 < 0 || position.z+6 >= Chunk::Z || position.z-6 < 0){
            return mastercraft::cube::TreeGenerator::Tree();
        }

        uint32_t trunk = Random::get(6u, 10u);
        Tree tree;

        for (uint32_t i = 0; i < trunk; i++) {
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i, position.z),
                              CubeType::WOOD_PLAIN);
        }

        for (uint32_t i = 1; i < 4; i++) {
            tree.emplace_back(glm::ivec3(position.x+i, position.y + 1 +4, position.z), CubeType::LEAVES_PLAIN);
            if(trunk  > 8) {
                tree.emplace_back(glm::ivec3(position.x - i, position.y + 1 + 7, position.z),
                                  CubeType::LEAVES_PLAIN);
            }

        }

        if(trunk > 8){
            //one floor
            tree.emplace_back(glm::ivec3(position.x - 1, position.y + 1 + 7, position.z-1), CubeType::LEAVES_PLAIN);
            tree.emplace_back(glm::ivec3(position.x - 1, position.y + 1 + 7, position.z+1), CubeType::LEAVES_PLAIN);
            tree.emplace_back(glm::ivec3(position.x - 2, position.y + 1 + 7, position.z-1), CubeType::LEAVES_PLAIN);
            tree.emplace_back(glm::ivec3(position.x - 2, position.y + 1 + 7, position.z+1), CubeType::LEAVES_PLAIN);

            //two floor
            tree.emplace_back(glm::ivec3(position.x - 1, position.y + 1 + 8, position.z+1), CubeType::LEAVES_PLAIN);
            tree.emplace_back(glm::ivec3(position.x - 2, position.y + 1 + 8, position.z-1), CubeType::LEAVES_PLAIN);
            tree.emplace_back(glm::ivec3(position.x - 2, position.y + 1 + 8, position.z), CubeType::LEAVES_PLAIN);
            tree.emplace_back(glm::ivec3(position.x - 1, position.y + 1 + 8, position.z), CubeType::LEAVES_PLAIN);


        }

        //one floor
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +4, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +4, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +4, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +4, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +4, position.z+2), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +4, position.z-2), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +4, position.z+2), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +4, position.z-2), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +4, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +4, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+4, position.y + 1 +4, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+4, position.y + 1 +4, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+4, position.y + 1 +4, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+5, position.y + 1 +4, position.z), CubeType::LEAVES_PLAIN);


        //two floor
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +5, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +5, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +5, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +5, position.z-2), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +5, position.z+2), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +5, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +5, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+4, position.y + 1 +5, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +5, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +5, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +5, position.z), CubeType::LEAVES_PLAIN);

        //three floor
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +6, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +6, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +6, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +6, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +6, position.z), CubeType::LEAVES_PLAIN);


        //head one floor
        tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +trunk, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +trunk, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x, position.y + 1 +trunk, position.z), CubeType::LEAVES_PLAIN);

        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +trunk, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +trunk, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x, position.y + 1 +trunk, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x, position.y + 1 +trunk, position.z-1), CubeType::LEAVES_PLAIN);

        //head two floor
        tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +trunk + 1, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk + 1, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x, position.y + 1 +trunk + 1, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 +trunk + 1, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x-2, position.y + 1 +trunk + 1, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x-2, position.y + 1 +trunk + 1, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x-2, position.y + 1 +trunk + 1, position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 +trunk + 1, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 +trunk + 1, position.z-1), CubeType::LEAVES_PLAIN);


        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk +1 , position.z-1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk + 1, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x, position.y + 1 +trunk+ 1, position.z+1), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x, position.y + 1 +trunk +1 , position.z-1), CubeType::LEAVES_PLAIN);

        //head three floor
        tree.emplace_back(glm::ivec3(position.x, position.y + 1 +trunk+ 2, position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk +2 , position.z), CubeType::LEAVES_PLAIN);
        tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 +trunk+ 2, position.z), CubeType::LEAVES_PLAIN);


        return tree;


    }
    
    
    TreeGenerator::Tree TreeGenerator::jungleTree(glm::vec3 position) {
        if(position.x+6 >= Chunk::X || position.x-6 < 0 || position.z+6 >= Chunk::Z || position.z-6 < 0){
            return mastercraft::cube::TreeGenerator::Tree();
        }

        uint32_t trunk = Random::get(4u, 5u);
        Tree tree;
        for (uint32_t i = 0; i < 2; i++) {
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i, position.z),
                              CubeType::WOOD_JUNGLE);
        }
        if(trunk == 4) {
            for (uint32_t i = 0; i < 2; i++) {
                tree.emplace_back(glm::ivec3(position.x+1+i, position.y + 1 + i + 2, position.z),
                                  CubeType::WOOD_JUNGLE);
                tree.emplace_back(glm::ivec3(position.x , position.y + 1 + i + 2, position.z),
                                  CubeType::WOOD_JUNGLE);
            }
            //one floor
            tree.emplace_back(glm::ivec3(position.x , position.y + 1 + trunk, position.z),
                              CubeType::WOOD_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+2, position.y + 1  +trunk, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1   +trunk, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+4, position.y + 1   +trunk, position.z), CubeType::LEAVES_JUNGLE);

            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 +trunk, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+2, position.y + 1  +trunk, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1   +trunk, position.z-1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+2, position.y + 1   +trunk, position.z-1), CubeType::LEAVES_JUNGLE);

            //two floor
            tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 +trunk+1, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk+1, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1  +trunk +1, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x-1, position.y + 1   +trunk+1, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x-2, position.y + 1   +trunk+1, position.z), CubeType::LEAVES_JUNGLE);

            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk+1, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1  +trunk +1, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x-1, position.y + 1   +trunk+1, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 +trunk+1, position.z-1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1  +trunk +1, position.z-1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x-1, position.y + 1   +trunk+1, position.z-1), CubeType::LEAVES_JUNGLE);



        }
        else{
            for (uint32_t i = 0; i < 3; i++) {
                tree.emplace_back(glm::ivec3(position.x +1 +i, position.y + 1 + i + 2, position.z),
                        CubeType::WOOD_JUNGLE);
            }

            //one floor
            tree.emplace_back(glm::ivec3(position.x+3+1, position.y + 1 +trunk, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3+2, position.y + 1  +trunk, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3+3, position.y + 1   +trunk, position.z), CubeType::LEAVES_JUNGLE);

            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 + trunk, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3-1, position.y + 1 + trunk, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3-2, position.y + 1 + trunk, position.z), CubeType::LEAVES_JUNGLE);

            tree.emplace_back(glm::ivec3(position.x+3+2, position.y + 1 +trunk, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3+1, position.y + 1  +trunk, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1   +trunk, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3-1, position.y + 1   +trunk, position.z+1), CubeType::LEAVES_JUNGLE);

            tree.emplace_back(glm::ivec3(position.x+3+2, position.y + 1 +trunk, position.z-1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3+1, position.y + 1  +trunk, position.z-1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1   +trunk, position.z-1), CubeType::LEAVES_JUNGLE);

            //two floor
            tree.emplace_back(glm::ivec3(position.x+3+1, position.y + 1 +trunk +1 , position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3+2, position.y + 1  +trunk + 1, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1 + trunk+1, position.z), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3-1, position.y + 1 + trunk+1, position.z), CubeType::LEAVES_JUNGLE);

            tree.emplace_back(glm::ivec3(position.x+3+1, position.y + 1  +trunk +1, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3, position.y + 1   +trunk +1, position.z+1), CubeType::LEAVES_JUNGLE);
            tree.emplace_back(glm::ivec3(position.x+3+1, position.y + 1   +trunk+1, position.z-1), CubeType::LEAVES_JUNGLE);
        }

        return tree;

        //return mastercraft::cube::TreeGenerator::Tree();
    }
    
    
    TreeGenerator::Tree TreeGenerator::snowTree(glm::vec3 position) {
        if(position.x+2 >= Chunk::X || position.x-2 < 0 || position.z+2 >= Chunk::Z || position.z-2 < 0){
            return mastercraft::cube::TreeGenerator::Tree();
        }
        uint32_t trunk = Random::get(2u, 3u);

        uint32_t leaves = Random::get(0u, 3u);

        Tree tree;
        if(leaves != 0) {
            for (uint32_t i = 0; i < trunk; i++) {
                tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i, position.z),
                                  CubeType::WOOD_SNOW);
            }
        } else{
            tree.emplace_back(glm::ivec3(position.x, position.y + 1, position.z),
                              CubeType::WOOD_SNOW);
        }

        for (uint32_t i = 0; i < leaves; i++) {
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i*3+trunk, position.z), CubeType::WOOD_SNOW);
            // one floor
            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 + i*3 +1 +trunk, position.z), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 + i*3 +1 +trunk, position.z), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i*3 +1 +trunk, position.z+1), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i*3 +1 +trunk, position.z-1), CubeType::LEAVES_SNOW);

            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 + i*3 +1 +trunk, position.z+1), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 + i*3+ 1 +trunk, position.z+1), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 + i*3 +1 +trunk, position.z+1), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 + i*3 +1 +trunk, position.z-1), CubeType::LEAVES_SNOW);

            tree.emplace_back(glm::ivec3(position.x+2, position.y + 1 + i*3+ 1 + trunk, position.z), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x-2, position.y + 1 + i*3 +1 +trunk, position.z), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i*3+ 1+trunk, position.z+2), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i*3+ 1 +trunk, position.z-2), CubeType::LEAVES_SNOW);


            // two floor
            tree.emplace_back(glm::ivec3(position.x+1, position.y + 1 + i*3 +2 +trunk, position.z), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x-1, position.y + 1 + i*3 + 2 +trunk, position.z), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i*3 + 2+trunk, position.z+1), CubeType::LEAVES_SNOW);
            tree.emplace_back(glm::ivec3(position.x, position.y + 1 + i*3 + 2 +trunk, position.z-1), CubeType::LEAVES_SNOW);



        }
        //three floor
        if(leaves != 0) {
            tree.emplace_back(
                    glm::ivec3(position.x, position.y + 1 + leaves * 3 + trunk, position.z),
                    CubeType::LEAVES_SNOW);
        }
        return tree;
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
                if (Random::get<bool>(0.01)) {
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
