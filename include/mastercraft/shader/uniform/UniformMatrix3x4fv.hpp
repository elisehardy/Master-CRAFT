#ifndef MASTERCRAFT_UNIFORMMATRIX34_HPP
#define MASTERCRAFT_UNIFORMMATRIX34_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix3x4fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX34_HPP
