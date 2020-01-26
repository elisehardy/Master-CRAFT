#ifndef MASTERCRAFT_UNIFORM3uiv_HPP
#define MASTERCRAFT_UNIFORM3uiv_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Uniform3uiv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORM3uiv_HPP
