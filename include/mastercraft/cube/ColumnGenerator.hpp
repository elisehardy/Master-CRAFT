#ifndef MASTERCRAFT_COLUMNGENERATOR_HPP
#define MASTERCRAFT_COLUMNGENERATOR_HPP

#include <array>

#include <GL/glew.h>

#include <mastercraft/cube/CubeType.hpp>
#include <mastercraft/cube/SuperChunk.hpp>


namespace mastercraft::cube {
    
    class ColumnGenerator {
        
        private:
            static std::array<cube::CubeType, cube::SuperChunk::Y> waterColumn(GLubyte height);
            
            static std::array<cube::CubeType, cube::SuperChunk::Y> sandColumn(GLubyte height);
            
            static std::array<cube::CubeType, cube::SuperChunk::Y> dirtColumn(GLubyte height);
            
            static std::array<cube::CubeType, cube::SuperChunk::Y> stoneColumn(GLubyte height);
            
            static std::array<cube::CubeType, cube::SuperChunk::Y> snowColumn(GLubyte height);
        
        public:
            
            ColumnGenerator() = delete;
            
            static std::array<cube::CubeType, cube::SuperChunk::Y> generateColumn(GLubyte height, cube::CubeType type);
    };
}

#endif //MASTERCRAFT_COLUMNGENERATOR_HPP
