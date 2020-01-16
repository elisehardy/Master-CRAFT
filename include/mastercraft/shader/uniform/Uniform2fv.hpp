#ifndef MASTERCRAFT_UNIFORM2FV_HPP
#define MASTERCRAFT_UNIFORM2FV_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class Uniform2fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM2FV_HPP
