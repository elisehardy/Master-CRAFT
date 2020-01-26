#ifndef MASTERCRAFT_UNIFORM2uiv_HPP
#define MASTERCRAFT_UNIFORM2uiv_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform2uiv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM2uiv_HPP
