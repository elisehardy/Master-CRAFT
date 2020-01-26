#ifndef MASTERCRAFT_ISINGLETON_HPP
#define MASTERCRAFT_ISINGLETON_HPP

#include "INonCopyable.hpp"


namespace mastercraft::util {
    
    /**
     * Common interface for Singletons.
     */
    class ISingleton : public INonCopyable {
        
        protected:
            
            ISingleton() = default;
        
        public:
            
            /**
             * Delete move constructor.
             */
            ISingleton(ISingleton &&) = delete;
    };
}

#endif //MASTERCRAFT_ISINGLETON_HPP
