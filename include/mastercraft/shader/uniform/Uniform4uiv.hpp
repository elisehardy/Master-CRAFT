#ifndef MASTERCRAFT_UNIFORM4uiv_HPP
#define MASTERCRAFT_UNIFORM4uiv_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform4uiv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM4uiv_HPP
