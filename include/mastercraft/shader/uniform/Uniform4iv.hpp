#ifndef MASTERCRAFT_UNIFORM4iv_HPP
#define MASTERCRAFT_UNIFORM4iv_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform4iv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM4iv_HPP
