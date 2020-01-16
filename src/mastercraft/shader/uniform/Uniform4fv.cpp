#include <mastercraft/shader/uniform/Uniform4fv.hpp>


namespace mastercraft::shader {
    
    void Uniform4fv::load(const void *value) {
        glUniform4fv(this->location, 1, static_cast<const GLfloat *>(value));
    }
}
