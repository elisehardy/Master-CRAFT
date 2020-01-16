#include <mastercraft/shader/uniform/UniformMatrix2fv.hpp>


namespace mastercraft::shader {
    
    void UniformMatrix2fv::load(const void *value) {
        glUniformMatrix2fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}
