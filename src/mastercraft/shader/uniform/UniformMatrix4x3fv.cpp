#include <mastercraft/shader/uniform/UniformMatrix4x3fv.hpp>


namespace mastercraft::shader {
    
    void UniformMatrix4x3fv::load(const void *value) {
        glUniformMatrix4x3fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}
