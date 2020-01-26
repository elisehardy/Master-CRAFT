#ifndef MASTERCRAFT_UNIFORMMATRIX42_HPP
#define MASTERCRAFT_UNIFORMMATRIX42_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix4x2fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX42_HPP
