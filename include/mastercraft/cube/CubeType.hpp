#ifndef MASTERCRAFT_CUBETYPE_HPP
#define MASTERCRAFT_CUBETYPE_HPP

#include <GL/glew.h>

namespace mastercraft::cube {
    
    static constexpr GLushort TRANSPARENT = 1 << 11;
    static constexpr GLushort ANIMATED = 1 << 12;
    
    static constexpr GLushort textureLoc(GLubyte x, GLubyte y) {
        return x | (y << 4);
    }
    
    enum CubeType : GLushort {
        AIR = 0 | TRANSPARENT, // Empty block, not present in the texture atlas.
        WATER = textureLoc(0, 0) | TRANSPARENT | ANIMATED,
        SAND_BEACH = textureLoc(2, 0),
        ICE = textureLoc(3, 0),
        SNOW = textureLoc(4, 0),
        STONE = textureLoc(5, 0),
        STONE_SNOW = textureLoc(6, 0),
        FLOWERS = textureLoc(7, 0)| TRANSPARENT,
        DIRT_PLAIN = textureLoc(2, 1) ,
        DIRT_JUNGLE = textureLoc(3, 1),
        DIRT_SNOW = textureLoc(4, 1),
        SAND_DESERT = textureLoc(5, 1),
        WOOD_PLAIN = textureLoc(2, 2),
        WOOD_JUNGLE = textureLoc(3, 2),
        WOOD_SNOW = textureLoc(4, 2),
        CACTUS = textureLoc(5, 2) | TRANSPARENT,
        LEAVES_PLAIN = textureLoc(2, 3) | TRANSPARENT,
        LEAVES_JUNGLE = textureLoc(3, 3) | TRANSPARENT,
        LEAVES_SNOW = textureLoc(4, 3) | TRANSPARENT
    };
}

#endif //MASTERCRAFT_CUBETYPE_HPP
