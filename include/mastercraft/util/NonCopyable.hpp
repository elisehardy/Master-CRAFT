#ifndef MASTERCRAFT_NONCOPYABLE_HPP
#define MASTERCRAFT_NONCOPYABLE_HPP

namespace mastercraft::util {
    
    class NonCopyable {
        public:
            NonCopyable(const NonCopyable &) = delete;
            NonCopyable &operator=(const NonCopyable &) = delete;
        
        protected:
            NonCopyable() = default;
            ~NonCopyable() = default;
    };
}

#endif //MASTERCRAFT_NONCOPYABLE_HPP
