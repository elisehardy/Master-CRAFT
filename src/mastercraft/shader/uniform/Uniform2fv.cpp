#include <mastercraft/shader/uniform/Uniform2fv.hpp>


namespace mastercraft::shader {
    
    void Uniform2fv::load(const void *value) {
        glUniform2fv(this->location, 1, static_cast<const GLfloat *>(value));
    }
}
