#ifndef MASTERCRAFT_UNIFORMMAXTRIX3_HPP
#define MASTERCRAFT_UNIFORMMAXTRIX3_HPP

#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class UniformMatrix3fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //MASTERCRAFT_UNIFORMMAXTRIX3_HPP
