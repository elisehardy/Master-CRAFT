#ifndef MASTERCRAFT_UNIFORMMATRIX2_HPP
#define MASTERCRAFT_UNIFORMMATRIX2_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix2fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX2_HPP
