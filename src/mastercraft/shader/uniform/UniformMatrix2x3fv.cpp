#include <mastercraft/shader/uniform/UniformMatrix2x3fv.hpp>


namespace mastercraft::shader {
    
    void UniformMatrix2x3fv::load(const void *value) {
        glUniformMatrix2x3fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}
