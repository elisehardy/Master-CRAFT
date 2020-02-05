#ifndef MASTERCRAFT_CHUNK_H
#define MASTERCRAFT_CHUNK_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <mastercraft/cube/CubeType.hpp>
#include <mastercraft/cube/CubeDirection.hpp>
#include <mastercraft/util/INonCopyable.hpp>
#include <vector>


namespace mastercraft::cube {
    
    class Chunk : public util::INonCopyable {
        public:
            static constexpr GLint X = 16;
            static constexpr GLint Y = 16;
            static constexpr GLint Z = 16;
            static constexpr GLint SIZE = X * Y * Z;
        
        private:
            static constexpr GLuint VERTEX_ATTR_POSITION = 0;
            static constexpr GLuint VERTEX_ATTR_NORMAL = 1;
            static constexpr GLuint VERTEX_ATTR_TEXTURE = 2;
            static constexpr GLuint VERTEX_ATTR_DATA = 3;
        
            CubeType cubes[X][Y][Z] {};
            glm::ivec3 position = glm::ivec3(0);
            GLboolean modified = true;
            GLuint countAlpha = 0;
            GLuint vboAlpha = 0;
            GLuint vaoAlpha = 0;
            GLuint count = 0;
            GLuint vbo = 0;
            GLuint vao = 0;
        
            [[nodiscard]] static bool onBorder(GLubyte x, GLubyte y, GLubyte z);
            
            [[nodiscard]] bool occluded(CubeType type, GLint x, GLint y, GLint z, CubeDirection direction) const;
        
            [[nodiscard]] GLushort computeData(CubeType type, CubeDirection direction, bool opaqueAbove) const;
        public:
            
            Chunk();
            
            ~Chunk();
        
            CubeType get(GLubyte x, GLubyte y, GLubyte z);
            
            void set(GLubyte x, GLubyte y, GLubyte z, CubeType type);
            
            void setPosition(GLint x, GLint y, GLint z);
        
            void touch();
        
            GLuint update();
            
            GLuint render(bool alpha);
    };
}

#endif // MASTERCRAFT_CHUNK_H
