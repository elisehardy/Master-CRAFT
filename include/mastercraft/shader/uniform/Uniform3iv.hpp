#ifndef MASTERCRAFT_UNIFORM3iv_HPP
#define MASTERCRAFT_UNIFORM3iv_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform3iv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM3iv_HPP
