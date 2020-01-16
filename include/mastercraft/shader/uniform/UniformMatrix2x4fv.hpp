#ifndef MASTERCRAFT_UNIFORMMATRIX24_HPP
#define MASTERCRAFT_UNIFORMMATRIX24_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix2x4fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX24_HPP
