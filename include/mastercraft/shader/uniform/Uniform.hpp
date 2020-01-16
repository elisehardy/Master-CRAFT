#ifndef MASTERCRAFT_UNIFORM_HPP
#define MASTERCRAFT_UNIFORM_HPP

#include <GL/glew.h>


namespace mastercraft::shader {
    
    enum UniformType : GLubyte {
        UNIFORM_1_F, UNIFORM_2_F, UNIFORM_3_F, UNIFORM_4_F,
        UNIFORM_1_I, UNIFORM_2_I, UNIFORM_3_I, UNIFORM_4_I,
        UNIFORM_1_UI,UNIFORM_2_UI,UNIFORM_3_UI, UNIFORM_4_UI,
        UNIFORM_MATRIX_2F, UNIFORM_MATRIX_3F, UNIFORM_MATRIX_4F,
        UNIFORM_MATRIX_2X3F, UNIFORM_MATRIX_3X2F,
        UNIFORM_MATRIX_2X4F, UNIFORM_MATRIX_4X2F,
        UNIFORM_MATRIX_3X4F, UNIFORM_MATRIX_4X3F
    };
    
    class Uniform {
        
        protected:
            const GLchar *name;
            GLuint program;
            GLint location;
        
        public:
            
            Uniform(GLuint program, const GLchar *name);
        
            virtual void load(const void *value) = 0;
    };
}

#endif // MASTERCRAFT_UNIFORM_HPP
