#ifndef MASTERCRAFT_CUBETYPE_HPP
#define MASTERCRAFT_CUBETYPE_HPP

namespace mastercraft::cube {
    
    static constexpr GLubyte ANIMATED = 0b10000000;
    
    enum CubeType : GLubyte {
        AIR = 0,
        WATER = 1 | ANIMATED,
        SAND = 2,
        DIRT = 3,
        STONE = 4,
        SNOW = 5,
        WOOD = 6,
        LEAVE
    };
}

#endif //MASTERCRAFT_CUBETYPE_HPP
