#ifndef MASTERCRAFT_UNIFORM4FV_HPP
#define MASTERCRAFT_UNIFORM4FV_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class Uniform4fv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM4FV_HPP
