#ifndef MASTERCRAFT_UNIFORMATRIX23_HPP
#define MASTERCRAFT_UNIFORMATRIX23_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix2x3fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMATRIX23_HPP
