#ifndef MASTERCRAFT_UNIFORMMATRIX32_HPP
#define MASTERCRAFT_UNIFORMMATRIX32_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix3x2fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX32_HPP
