#ifndef MASTERCRAFT_CUBETYPE_HPP
#define MASTERCRAFT_CUBETYPE_HPP

namespace mastercraft::cube {
    
    static constexpr GLubyte TRANSPARENT = 0b10000000;
    
    enum CubeType : GLubyte {
        AIR = 0 | TRANSPARENT,
        WATER = 1 | TRANSPARENT,
        SAND = 2,
        DIRT = 3,
        STONE = 4,
        SNOW = 5,
        JUNGLE_WOOD = 6,
        CACTUS = 7 | TRANSPARENT,
        OAK_WOOD = 8,
        JUNGLE_DIRT = 9,
        OAK_LEAVES = 10 | TRANSPARENT,
        JUNGLE_LEAVES = 11 | TRANSPARENT,
        DESERT_SAND = 12
    };
}

#endif //MASTERCRAFT_CUBETYPE_HPP
