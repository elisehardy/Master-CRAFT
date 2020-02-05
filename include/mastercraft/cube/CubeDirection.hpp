#ifndef MASTERCRAFT_CUBEDIRECTION_HPP
#define MASTERCRAFT_CUBEDIRECTION_HPP

namespace mastercraft::cube {
    
    static constexpr GLubyte BIT_FACE_OFFSET = 8;
    
    enum CubeDirection : GLushort {
        TOP = 0u << BIT_FACE_OFFSET,
        FACE = 1u << BIT_FACE_OFFSET,
        RIGHT = 2u << BIT_FACE_OFFSET,
        BACK = 3u << BIT_FACE_OFFSET,
        LEFT = 4u << BIT_FACE_OFFSET,
        BOTTOM = 5u << BIT_FACE_OFFSET
    };
}

#endif //MASTERCRAFT_CUBEDIRECTION_HPP

