#ifndef MASTERCRAFT_UNIFORM2uiv_HPP
#define MASTERCRAFT_UNIFORM2uiv_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class Uniform2uiv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM2uiv_HPP
