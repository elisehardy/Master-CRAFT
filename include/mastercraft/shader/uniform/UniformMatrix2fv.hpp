#ifndef MASTERCRAFT_UNIFORMMATRIX2_HPP
#define MASTERCRAFT_UNIFORMMATRIX2_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix2fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMATRIX2_HPP
