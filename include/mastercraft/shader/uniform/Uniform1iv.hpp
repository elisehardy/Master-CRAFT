#ifndef MASTERCRAFT_UNIFORM1iv_HPP
#define MASTERCRAFT_UNIFORM1iv_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class Uniform1iv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM1iv_HPP
