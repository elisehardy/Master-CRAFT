#ifndef MASTERCRAFT_UNIFORMMATRIX42_HPP
#define MASTERCRAFT_UNIFORMMATRIX42_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix4x2fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX42_HPP
