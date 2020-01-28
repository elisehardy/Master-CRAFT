#ifndef MASTERCRAFT_CUBETYPE_HPP
#define MASTERCRAFT_CUBETYPE_HPP

namespace mastercraft::cube {
    
    enum struct CubeType : GLbyte {
        AIR = 0,
        WATER,
        SAND,
        DIRT,
        STONE,
        SNOW,
        WOOD,
        LEAVE
    };
}

#endif //MASTERCRAFT_CUBETYPE_HPP
