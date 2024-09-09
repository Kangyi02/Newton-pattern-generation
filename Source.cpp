#include "Fractal.hpp"
#include "Complex.hpp"
#include "Pixel.hpp"
#include <iostream>
using namespace std;

Fractal testMoveConstructor(unsigned int rows, unsigned int cols)
{
	Fractal F(rows, cols);
	return F;
}

int main()
{
	Fractal m1(20U, 20U), m2, m3;
	saveToPPM(m1, "newton1.ppm");
	m2 = Fractal(m1);
	saveToPPM(m2, "newton2.ppm");
	m3 = testMoveConstructor(60U, 80U);
	saveToPPM(m3, "newton3.ppm");
	return 0;
}