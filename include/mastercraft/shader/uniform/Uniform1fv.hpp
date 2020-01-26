#ifndef MASTERCRAFT_UNIFORM1FV_HPP
#define MASTERCRAFT_UNIFORM1FV_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform1fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM1FV_HPP
