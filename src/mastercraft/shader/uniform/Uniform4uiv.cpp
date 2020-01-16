#include <mastercraft/shader/uniform/Uniform4uiv.hpp>


namespace mastercraft::shader {
    
    void Uniform4uiv::load(const void *value) {
        glUniform4uiv(this->location, 1, static_cast<const GLuint *>(value));
    }
}
