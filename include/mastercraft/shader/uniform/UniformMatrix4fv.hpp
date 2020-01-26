#ifndef MASTERCRAFT_UNIFORMMATRIX4_HPP
#define MASTERCRAFT_UNIFORMMATRIX4_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix4fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX4_HPP
