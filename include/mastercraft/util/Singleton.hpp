#ifndef MASTERCRAFT_SINGLETON_HPP
#define MASTERCRAFT_SINGLETON_HPP

#include "NonCopyable.hpp"


namespace mastercraft::util {
    class Singleton : public NonCopyable {
        public:
            // Delete move constructor
            Singleton(Singleton &&) = delete;
        
        protected:
            Singleton() = default;
    };
}

#endif // MASTERCRAFT_SINGLETON_HPP
