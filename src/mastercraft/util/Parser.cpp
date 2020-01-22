#include <regex>


#include <mastercraft/util/Parser.hpp>
#include <mastercraft/util/ParserException.hpp>


namespace mastercraft::util {

    void Parser::error(const std::string &what) const {

        throw ParserException(this->path, this->lin, this->col, what);
    }


    std::string Parser::read(const std::string &pattern, bool allowEmpty) {
        std::string tmp = std::string(1, char(this->file.get()));
        std::regex re { pattern };
        std::stringstream ss;

        while (std::regex_match(tmp, re)) {
            if (tmp == "\n") {
                this->lin++;
                this->col = 0;
            }
            else {
                this->col++;
            }

            ss << tmp;
            tmp = std::string(1, char(this->file.get()));
        }

        if (!allowEmpty && ss.str().empty()) {
            this->error("Next character does not match regex '" + pattern + "' (character '" + tmp + "' has been found"
            );
        }

        this->file.unget();

        return ss.str();
    }


    template<class I>
    I Parser::parseIntegral(uint8_t radix) {
        std::string s = this->read("\\d");
        size_t idx;
        long l;

        try {
            l = stol(s, &idx, radix);
        } catch (const std::invalid_argument &e) {
            this->error(e.what());
        } catch (const std::out_of_range &e) {
            this->error(e.what());
        }

        return static_cast<I>(l);
    }


    util::Point16 Parser::parseColor() {
        int16_t x, y;

        this->read("(\\s|\n)", true);
        this->read("\\(");

        this->read("(\\s|\n)", true);
        x = parseIntegral<short>();
        this->read("(\\s|\n)", true);
        this->read(",");
        this->read("(\\s|\n)", true);
        y = parseIntegral<short>();

        this->read("(\\s|\n)", true);
        this->read("\\)");

        return { x, y };
    }


    util::Point8 Parser::parseHeight() {
        int16_t x, y;

        this->read("(\\s|\n)", true);
        this->read("\\(");

        this->read("(\\s|\n)", true);
        x = parseIntegral<short>();
        this->read("(\\s|\n)", true);
        this->read(",");
        this->read("(\\s|\n)", true);
        y = parseIntegral<short>();

        this->read("(\\s|\n)", true);
        this->read("\\)");

        return { x, y };
    }





    /*util::Shape Parser::operator()(const std::string &path) {
        util::Shape shape;

        this->file = std::ifstream(path);
        this->path = path;
        this->lin = 0;
        this->col = 0;

        for (int i = 0; i < 7; i++) {
            shape.addPolygon(this->parsePolygon());
        }

        this->file.close();

        return shape;
    }*/
}
