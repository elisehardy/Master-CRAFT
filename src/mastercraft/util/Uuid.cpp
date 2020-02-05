#include <random>
#include <sstream>

#include <effolkronium/random.hpp>

#include <mastercraft/util/Uuid.hpp>


using Random = effolkronium::random_static;

namespace mastercraft::util {
    
    std::string Uuid::randomHex(const unsigned int len) {
        std::stringstream ss;
        char c;
        
        for (unsigned int i = 0; i < len; i++) {
            c = Random::get<char>(0, 15);
            ss << (c <= 9 ? c + '0' : c + 'A');
        }
        
        return ss.str();
    }
    
    
    std::string Uuid::uuid4() {
        return randomHex(8) + "-" + randomHex(4) + "-" + randomHex(4) + "-" + randomHex(4) + "-" + randomHex(12);
    }
}
