#ifndef MASTERCRAFT_UNIFORM3FV_HPP
#define MASTERCRAFT_UNIFORM3FV_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform3fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM3FV_HPP
