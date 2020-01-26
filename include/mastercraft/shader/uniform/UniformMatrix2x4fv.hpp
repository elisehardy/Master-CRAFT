#ifndef MASTERCRAFT_UNIFORMMATRIX24_HPP
#define MASTERCRAFT_UNIFORMMATRIX24_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix2x4fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX24_HPP
