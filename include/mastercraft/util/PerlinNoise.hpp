
#ifndef MASTERCRAFT_PERLINNOISE_H
#define MASTERCRAFT_PERLINNOISE_H

#include <vector>
#include <cmath>

class PerlinNoise {
    std::vector<int> p;
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    double noise(double x, double y, double z);
private:
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
};


#endif //MASTERCRAFT_PERLINNOISE_H
