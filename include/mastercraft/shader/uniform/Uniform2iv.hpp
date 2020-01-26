#ifndef MASTERCRAFT_UNIFORM2iv_HPP
#define MASTERCRAFT_UNIFORM2iv_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform2iv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM2iv_HPP
