#ifndef MASTERCRAFT_STATISTICS_HPP
#define MASTERCRAFT_STATISTICS_HPP

#include <GL/glew.h>


namespace mastercraft::game {
    
    struct Statistics {
        GLuint superchunk;
        GLuint chunk;
        GLuint cube;
        GLuint face;
        GLuint entity;
        GLuint fps;
        GLuint rendered_face;
        GLuint64 occludedFace;
        GLuint64 frustumCulledFace;
    };
}

#endif //MASTERCRAFT_STATISTICS_HPP
