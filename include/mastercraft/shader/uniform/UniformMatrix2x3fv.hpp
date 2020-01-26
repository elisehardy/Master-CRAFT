#ifndef MASTERCRAFT_UNIFORMATRIX23_HPP
#define MASTERCRAFT_UNIFORMATRIX23_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix2x3fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMATRIX23_HPP
