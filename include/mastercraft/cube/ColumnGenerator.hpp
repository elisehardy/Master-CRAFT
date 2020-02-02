#ifndef MASTERCRAFT_COLUMNGENERATOR_HPP
#define MASTERCRAFT_COLUMNGENERATOR_HPP

#include <array>

#include <GL/glew.h>

#include <mastercraft/cube/CubeType.hpp>
#include <mastercraft/cube/SuperChunk.hpp>


namespace mastercraft::cube {
    
    
    
    class ColumnGenerator {
        
        private:
            typedef std::array<cube::CubeType, cube::SuperChunk::Y> Column;
            
            static Column waterColumn(GLubyte height);
            
            static Column sandColumn(GLubyte height);
            
            static Column dirtColumn(GLubyte height);
            
            static Column stoneColumn(GLubyte height);
            
            static Column snowColumn(GLubyte height);
        
        public:
            
            ColumnGenerator() = delete;
            
            static std::array<cube::CubeType, cube::SuperChunk::Y> generate(GLubyte height, cube::CubeType type);
    };
}

#endif //MASTERCRAFT_COLUMNGENERATOR_HPP
