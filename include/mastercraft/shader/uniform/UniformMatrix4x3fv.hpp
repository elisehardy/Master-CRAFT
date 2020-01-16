#ifndef MASTERCRAFT_UNIFORMMATRIX43_HPP
#define MASTERCRAFT_UNIFORMMATRIX43_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix4x3fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX43_HPP
