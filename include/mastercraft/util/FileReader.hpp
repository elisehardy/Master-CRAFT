#ifndef MASTERCRAFT_FILEREADER_HPP
#define MASTERCRAFT_FILEREADER_HPP

#include <string>

namespace mastercraft::util {
    
    class FileReader {
        
        public:
            
            FileReader() = delete;
            
            static std::string read(const std::string &path);
    };
}

#endif // MASTERCRAFT_FILEREADER_HPP
