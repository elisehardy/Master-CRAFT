//
// Created by ehardy on 1/20/20.
//

#ifndef MASTERCRAFT_PARSEREXCEPTION_HPP
#define MASTERCRAFT_PARSEREXCEPTION_HPP


#include <cstdint>
#include <string>


namespace mastercraft::util {

    class ParserException : public std::exception {

    private:
        const std::string path;
        const uint16_t lin;
        const uint16_t col;
        const std::string msg;

    public:
        ParserException(std::string t_path, uint16_t t_lin, uint16_t t_col, std::string t_msg);

        ~ParserException() override = default;

        [[nodiscard]] std::string getPath() const;

        [[nodiscard]] uint16_t getLine() const;

        [[nodiscard]] uint16_t getColumn() const;

        [[nodiscard]] std::string getMessage() const;

        [[nodiscard]] const char *what() const noexcept override;
    };
}


#endif //MASTERCRAFT_PARSEREXCEPTION_HPP
