#ifndef MASTERCRAFT_UNIFORMMATRIX43_HPP
#define MASTERCRAFT_UNIFORMMATRIX43_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix4x3fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX43_HPP
