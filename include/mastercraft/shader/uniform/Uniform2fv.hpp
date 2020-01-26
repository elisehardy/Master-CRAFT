#ifndef MASTERCRAFT_UNIFORM2FV_HPP
#define MASTERCRAFT_UNIFORM2FV_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform2fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM2FV_HPP
