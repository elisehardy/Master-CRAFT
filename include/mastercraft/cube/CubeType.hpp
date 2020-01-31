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
        WOOD = 6,
        LEAF
    };
}

#endif //MASTERCRAFT_CUBETYPE_HPP
