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
            
            [[nodiscard]] static Column waterColumn(GLuint height);
        
            [[nodiscard]] static Column iceColumn(GLuint height);
        
            [[nodiscard]] static Column sandBeachColumn(GLuint height);
        
            [[nodiscard]] static Column sandDesertColumn(GLuint height);
        
            [[nodiscard]] static Column snowColumn(GLuint height);
        
            [[nodiscard]] static Column stoneColumn(GLuint height);
        
            [[nodiscard]] static Column stoneSnowColumn(GLuint height);
        
            [[nodiscard]] static Column dirtPlainColumn(GLuint height);
        
            [[nodiscard]] static Column dirtJungleColumn(GLuint height);
        
            [[nodiscard]] static Column dirtSnowColumn(GLuint height);
        
        public:
            
            ColumnGenerator() = delete;
        
            [[nodiscard]] static std::array<CubeType, SuperChunk::Y> generate(GLuint height, CubeType type);
    };
}

#endif //MASTERCRAFT_COLUMNGENERATOR_HPP
