

#ifndef MASTERCRAFT_PARSER_HPP
#define MASTERCRAFT_PARSER_HPP

#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>

#include <mastercraft/util/Point.hpp>

namespace mastercraft::util {



    class Parser {

    private:
        std::ifstream file = {};
        std::string path = {};
        uint16_t lin = 0;
        uint16_t col = 0;

        [[noreturn]] void error(const std::string &what) const;

        std::string read(const std::string &pattern, bool allowEmpty = false);

        template<class I>
        I parseIntegral(uint8_t radix = 10);

        util::Point16 parseColor();

        util::Point8 parseHeight();



    public:

        Parser() = default;

        //util::Shape operator()(const std::string &path);
    };
}



#endif //MASTERCRAFT_PARSER_HPP
