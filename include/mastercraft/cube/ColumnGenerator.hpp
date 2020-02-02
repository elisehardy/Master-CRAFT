#ifndef MASTERCRAFT_COLUMNGENERATOR_HPP
#define MASTERCRAFT_COLUMNGENERATOR_HPP

#include <array>

#include <GL/glew.h>

#include <mastercraft/cube/CubeType.hpp>
#include <mastercraft/cube/SuperChunk.hpp>


namespace mastercraft::cube {
    
    
    
    class ColumnGenerator {
        
        private:
            typedef std::array<CubeType, SuperChunk::Y> Column;
            
            [[nodiscard]] static Column waterColumn(GLubyte height);
        
            [[nodiscard]] static Column iceColumn(GLubyte height);
        
            [[nodiscard]] static Column sandBeachColumn(GLubyte height);
        
            [[nodiscard]] static Column sandDesertColumn(GLubyte height);
        
            [[nodiscard]] static Column snowColumn(GLubyte height);
        
            [[nodiscard]] static Column stoneColumn(GLubyte height);
        
            [[nodiscard]] static Column stoneSnowColumn(GLubyte height);
        
            [[nodiscard]] static Column dirtPlainColumn(GLubyte height);
        
            [[nodiscard]] static Column dirtJungleColumn(GLubyte height);
        
            [[nodiscard]] static Column dirtSnowColumn(GLubyte height);
        
        public:
            
            ColumnGenerator() = delete;
        
            [[nodiscard]] static std::array<CubeType, SuperChunk::Y> generate(GLubyte height, CubeType type);
    };
}

#endif //MASTERCRAFT_COLUMNGENERATOR_HPP
