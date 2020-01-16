#ifndef MASTERCRAFT_CUBETYPE_HPP
#define MASTERCRAFT_CUBETYPE_HPP

namespace mastercraft::world {
    
    enum CubeType : GLbyte {
        INODE = -1,
        AIR = 0,
        DIRT,
        STONE,
        SAND
    };
}
#endif //MASTERCRAFT_CUBETYPE_HPP
