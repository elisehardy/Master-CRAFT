//
// Created by ehardy on 1/6/20.
//

#ifndef MASTERCRAFT_PPM_H
#define MASTERCRAFT_PPM_H

#include <iostream>
#include <vector>

class PPM {
    void init();
    unsigned int nr_lines;
    unsigned int nr_columns;

public:
    std::vector<unsigned char> r;
    std::vector<unsigned char> g;
    std::vector<unsigned char> b;
    unsigned int height;
    unsigned int width;
    unsigned int max_col_val;
    unsigned int size;

    PPM();

    PPM(const std::string &fname);

    PPM(unsigned int _width, unsigned int _height);

    void read(const std::string &fname);

    void write(const std::string &fname);
};
#endif //MASTERCRAFT_PPM_H
