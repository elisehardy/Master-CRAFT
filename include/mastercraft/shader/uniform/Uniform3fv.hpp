#ifndef MASTERCRAFT_UNIFORM3FV_HPP
#define MASTERCRAFT_UNIFORM3FV_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class Uniform3fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM3FV_HPP
