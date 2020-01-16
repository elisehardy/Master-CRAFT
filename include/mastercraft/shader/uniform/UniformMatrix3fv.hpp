#ifndef MASTERCRAFT_UNIFORMMAXTRIX3_HPP
#define MASTERCRAFT_UNIFORMMAXTRIX3_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix3fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMAXTRIX3_HPP
