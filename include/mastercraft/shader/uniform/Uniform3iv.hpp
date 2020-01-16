#ifndef MASTERCRAFT_UNIFORM3iv_HPP
#define MASTERCRAFT_UNIFORM3iv_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class Uniform3iv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM3iv_HPP
