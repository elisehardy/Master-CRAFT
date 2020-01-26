#ifndef MASTERCRAFT_UNIFORM1uiv_HPP
#define MASTERCRAFT_UNIFORM1uiv_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform1uiv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM1uiv_HPP
