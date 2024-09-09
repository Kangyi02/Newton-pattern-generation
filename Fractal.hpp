#pragma once
#include "Pixel.hpp"
#include "Complex.hpp"
#include <algorithm>

class Fractal
{
private:
    unsigned int cols;
    Pixel** grid;
    static const unsigned int maxIter = 30;
    unsigned int rows;

    Pixel determinePixelColor(Complex Z);
    void makeNewtonFractal();

public:
    ~Fractal();
    Fractal();
    Fractal(const Fractal&);
    Fractal(Fractal&&);
    Fractal(unsigned int, unsigned int);
    const Fractal& operator=(const Fractal&);
    Fractal& operator=(Fractal&&);
    friend void saveToPPM(Fractal&, const char*);
};