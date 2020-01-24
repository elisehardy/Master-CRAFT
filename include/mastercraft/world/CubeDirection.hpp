#ifndef MASTERCRAFT_CUBEDIRECTION_HPP
#define MASTERCRAFT_CUBEDIRECTION_HPP

namespace mastercraft::world {
    
    enum struct CubeDirection : GLbyte {
        FACE,
        TOP,
        BACK,
        BOTTOM,
        LEFT,
        RIGHT
    };
}

#endif //MASTERCRAFT_CUBEDIRECTION_HPP
