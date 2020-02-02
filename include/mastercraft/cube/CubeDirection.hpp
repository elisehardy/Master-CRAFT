#ifndef MASTERCRAFT_CUBEDIRECTION_HPP
#define MASTERCRAFT_CUBEDIRECTION_HPP

namespace mastercraft::cube {
    
    enum CubeDirection : GLushort {
        TOP = 0 << 8,
        FACE = 1 << 8,
        RIGHT = 2 << 8,
        BACK = 3 << 8,
        LEFT = 4 << 8,
        BOTTOM = 5 << 8
    };
}

#endif //MASTERCRAFT_CUBEDIRECTION_HPP
