#ifndef MASTERCRAFT_TREEGENERATOR_HPP
#define MASTERCRAFT_TREEGENERATOR_HPP

#include <vector>
#include <utility>

#include <glm/vec3.hpp>

#include <mastercraft/cube/CubeType.hpp>


namespace mastercraft::cube {
    
    class TreeGenerator {
        
        private:
            typedef std::vector<std::pair<glm::ivec3, CubeType>> Tree;
        
            [[nodiscard]] static Tree plainTree(glm::vec3 position);
        
            [[nodiscard]] static Tree jungleTree(glm::vec3 position);
        
            [[nodiscard]] static Tree snowTree(glm::vec3 position);
        
            [[nodiscard]] static Tree cactus(glm::vec3 position);
            
        public:
            
            TreeGenerator() = delete;
        
            [[nodiscard]] static std::vector<std::pair<glm::ivec3, CubeType>> generate(glm::ivec3 position, CubeType biome);
    };
}

#endif //MASTERCRAFT_TREEGENERATOR_HPP
