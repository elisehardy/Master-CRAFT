#ifndef MASTERCRAFT_UNIFORMMATRIX32_HPP
#define MASTERCRAFT_UNIFORMMATRIX32_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix3x2fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX32_HPP
