#ifndef MASTERCRAFT_CUBETYPE_HPP
#define MASTERCRAFT_CUBETYPE_HPP

#include <GL/glew.h>


namespace mastercraft::cube {
    
    /**
     * Flag indicating the block us
     */
    static constexpr GLushort TRANSPARENT = 1 << 11;
    static constexpr GLushort ANIMATED = 1 << 12;
    static constexpr GLushort TOP_OVERLAY = 1 << 13;
    
    
    static constexpr GLushort textureLoc(GLushort x, GLushort y) {
        return x | (y << 4u);
    }
    
    enum CubeType : GLushort {
        AIR = 0u | TRANSPARENT, // Empty block, not present in the texture atlas.
        WATER = textureLoc(0, 0) | TRANSPARENT | ANIMATED,
        SAND_BEACH = textureLoc(2, 0),
        ICE = textureLoc(3, 0),
        SNOW = textureLoc(4, 0),
        STONE = textureLoc(5, 0),
        STONE_SNOW = textureLoc(6, 0) | TOP_OVERLAY,
        FLOWERS = textureLoc(7, 0) | TRANSPARENT,
        DIRT_PLAIN = textureLoc(2, 1) | TOP_OVERLAY,
        DIRT_JUNGLE = textureLoc(3, 1) | TOP_OVERLAY,
        DIRT_SNOW = textureLoc(4, 1) | TOP_OVERLAY,
        SAND_DESERT = textureLoc(5, 1),
        WOOD_PLAIN = textureLoc(2, 2),
        WOOD_JUNGLE = textureLoc(3, 2),
        WOOD_SNOW = textureLoc(4, 2),
        CACTUS = textureLoc(5, 2),
        LEAVES_PLAIN = textureLoc(2, 3) | TRANSPARENT,
        LEAVES_JUNGLE = textureLoc(3, 3) | TRANSPARENT,
        LEAVES_SNOW = textureLoc(4, 3) | TRANSPARENT
    };
}

#endif //MASTERCRAFT_CUBETYPE_HPP
