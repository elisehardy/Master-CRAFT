#ifndef MASTERCRAFT_UNIFORMMATRIX4_HPP
#define MASTERCRAFT_UNIFORMMATRIX4_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix4fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX4_HPP
