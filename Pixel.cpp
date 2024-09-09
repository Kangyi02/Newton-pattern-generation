#include "Pixel.hpp"
#include <fstream>

Pixel::~Pixel() {}
Pixel::Pixel() :blue(0), green(0), red(0) { }
Pixel::Pixel(const Pixel& a) :blue(a.blue), green(a.green), red(a.red) { cout << "colour pixel:)" << endl; }
Pixel::Pixel(unsigned int a, unsigned int b, unsigned int c) : red(a), green(b), blue(c) {}

const unsigned int& Pixel::operator[](const char* a)
{
    if (a == "blue")
        return this->blue;
    else if (a == "green")
        return this->green;
    else if (a == "red")
        return this->red;
    else
        throw InputOutOfBoundsException("Error!", "OffendingIndex");
}

Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* em, const char* oi)
{
    this->errorMessage = em;
    this->offendingIndex = oi;
}

const char* Pixel::InputOutOfBoundsException::returnError()
{
    return errorMessage;
}

const char* Pixel::InputOutOfBoundsException::returnOffendingIndex()
{
    return offendingIndex;
}

ostream& operator<<(ostream& os, const Pixel& p)
{
    ofstream namefile;
    namefile.open("pixel.ppm");
    if (!namefile)
        cout << "ERROR: Cannot open the file." << endl;

    try
    {
        os << p[red] << " " << p.green << " " << p.blue;
    }
    catch (Pixel::InputOutOfBoundsException e)
    {
        cout << e.returnError();
        cout << e.returnOffendingIndex();
        exit(1);
    }
    namefile.close();

    return os;
}