#include <random>
#include <sstream>

#include <mastercraft/util/Uuid.hpp>


namespace mastercraft::util {

    
    unsigned int Uuid::randomChar() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        return dis(gen);
    }
    
    std::string Uuid::randomHex(const unsigned int len) {
        std::stringstream ss;
        
        for (unsigned int i = 0; i < len; i++) {
            const auto rc = randomChar();
            std::stringstream hexstream;
            hexstream << std::hex << rc;
            auto hex = hexstream.str();
            ss << (hex.length() < 2 ? '0' + hex : hex);
        }
        
        return ss.str();
    }
    
    std::string Uuid::uuid4() {
        return randomHex(8) + "-" + randomHex(4) + "-" + randomHex(4) + "-" + randomHex(4) + "-" + randomHex(12);
    }
}
