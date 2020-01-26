#ifndef MASTERCRAFT_UNIFORMMATRIX34_HPP
#define MASTERCRAFT_UNIFORMMATRIX34_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix3x4fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX34_HPP
