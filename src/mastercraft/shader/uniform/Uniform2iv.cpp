#include <mastercraft/shader/uniform/Uniform2iv.hpp>


namespace mastercraft::shader {
    
    void Uniform2iv::load(const void *value) {
        glUniform2iv(this->location, 1, static_cast<const GLint *>(value));
    }
}
