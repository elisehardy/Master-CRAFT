#ifndef MASTERCRAFT_OBJ_HPP
#define MASTERCRAFT_OBJ_HPP

#include <vector>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <mastercraft/entity/EntityVertex.hpp>


namespace mastercraft::util {
    
    class OBJ {
        public:
            
            OBJ() = delete;
            
            static std::vector<entity::EntityVertex> Load(const std::string &path);
    };
}

#endif //MASTERCRAFT_OBJ_HPP
