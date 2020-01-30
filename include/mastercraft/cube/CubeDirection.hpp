#ifndef MASTERCRAFT_CUBEDIRECTION_HPP
#define MASTERCRAFT_CUBEDIRECTION_HPP

namespace mastercraft::cube {
    
    enum CubeDirection : GLubyte {
        TOP = 0 << 4,
        FACE = 1 << 4,
        RIGHT = 2 << 4,
        BACK = 3 << 4,
        LEFT = 4 << 4,
        BOTTOM = 5 << 4
    };
}

#endif //MASTERCRAFT_CUBEDIRECTION_HPP
