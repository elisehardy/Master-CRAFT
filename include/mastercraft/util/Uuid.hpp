#ifndef MASTERCRAFT_UUID_HPP
#define MASTERCRAFT_UUID_HPP

#include <string>

namespace mastercraft::util {
    
    class Uuid {
        private:
            static unsigned int randomChar();
            
            static std::string randomHex(unsigned int len);
            
        public:
            static std::string uuid4();
    };
    
}

#endif // MASTERCRAFT_UUID_HPP
