#ifndef MASTERCRAFT_CHUNK_H
#define MASTERCRAFT_CHUNK_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <mastercraft/cube/CubeType.hpp>
#include <mastercraft/cube/CubeDirection.hpp>
#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::cube {
    
    class Chunk : public util::INonCopyable {
        public:
            static constexpr GLubyte X = 16;
            static constexpr GLubyte Y = 16;
            static constexpr GLubyte Z = 16;
            static constexpr GLuint SIZE = X * Y * Z;
        
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
            static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
            static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;
            static constexpr GLuint VERTEX_ATTR_TYPE = 3;
            
            CubeType cubes[X][Y][Z];
            GLboolean modified;
            GLuint count;
            GLuint vbo;
            GLuint vao;
            
            [[nodiscard]] bool occluded(GLubyte x, GLubyte y, GLubyte z, CubeDirection direction) const;
        
        public:
            
            Chunk();
        
            ~Chunk();
            
            CubeType get(GLubyte x, GLubyte y, GLubyte z);
            
            void set(GLubyte x, GLubyte y, GLubyte z, CubeType type);
            
            GLuint update();
            
            GLuint render();
    };
}

#endif // MASTERCRAFT_CHUNK_H
