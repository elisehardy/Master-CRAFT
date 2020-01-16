#ifndef MASTERCRAFT_UNIFORM3uiv_HPP
#define MASTERCRAFT_UNIFORM3uiv_HPP

#include <mastercraft/shader/uniform/Uniform.hpp>


namespace mastercraft::shader {
    
    class Uniform3uiv : public Uniform {
        
        public:
        
            using Uniform::Uniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM3uiv_HPP
