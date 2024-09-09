#include "Fractal.hpp"
#include <fstream>

Pixel Fractal::determinePixelColor(Complex Z)
{
    double tol = 1E-4, diff = 1.0, test = 0.58974;
    unsigned int iter = 0, color = 0;
    Complex Znew;

    while (iter < 512)
    {
        iter++;
        Znew = Z - ((Z * Z * Z) - (2.0 * Z) + 2.0) / ((3.0 * Z * Z) - 2.0);
        diff = getMagnitude(Z - Znew);
        Z = Znew;
        if (diff < tol)
        {
            color = maxIter - min(iter, maxIter);
            if (abs(Z["imag"]) < tol)
            {
                return Pixel(color, color, 0);
            }
            else if (abs(Z["imag"] - test) < tol)
            {
                return Pixel(0, color, color);
            }
            else if (abs(Z["imag"] + test) < tol)
            {
                return Pixel(color, 0, color);
            }
        }
    }
    return Pixel(0, 0, 0);
}

void Fractal::makeNewtonFractal()
{
    cout << "> Now creating the Newton Fractal ..." << endl;
    Complex Z;
    double step_height = 4.0 / rows;
    double step_width = 4.0 / cols;
    for (unsigned int j = 0; j < rows; j++)
    {
        for (unsigned int k = 0; k < cols; k++)
        {
            Z["imag"] = 2.0 - (j * step_height);
            Z["real"] = (k * step_width) - 2.0;
            grid[j][k] = determinePixelColor(Z);
        }
    }
}

Fractal::~Fractal()
{
    cout << "> Destructor called ..." << endl;
    for (int i = 0; i < rows; i++)
    {
        delete[] grid[i];
        grid[i] = nullptr;
    }

    delete[] grid;
}

Fractal::Fractal() : cols(0), rows(0)
{
    cout << "> Default constructor called ... " << endl;
    this->grid = new Pixel * [rows];
    for (int i = 0; i < rows; i++)
        grid[i] = new Pixel[cols];

}

Fractal::Fractal(const Fractal& m) : cols(m.cols), rows(m.rows)
{
    cout << "> Copy constructor called ..." << endl;

    grid = new Pixel * [rows];
    for (int i = 0; i < rows; i++)
        grid[i] = new Pixel[cols];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = m.grid[i][j];
}

Fractal::Fractal(Fractal&& m)
{
    cout << "> Move constructor called ..." << endl;

    cols = m.cols;
    rows = m.rows;
    grid = m.grid;

    m.cols = 0;
    m.rows = 0;
    m.grid = nullptr;
}

Fractal::Fractal(unsigned int c, unsigned int r) : cols(c), rows(r)
{
    cout << "> Two-arg constructor called ..." << endl;
    grid = new Pixel * [rows];
    for (int i = 0; i < rows; i++)
        grid[i] = new Pixel[cols];
    makeNewtonFractal();
}

const Fractal& Fractal::operator=(const Fractal& m)
{
    if (this != &m)
    {
        if (grid != nullptr)
            for (int i = 0; i < rows; i++)
            {
                delete[] grid[i];
                delete grid;
            }
        this->rows = m.rows;
        this->cols = m.cols;
        this->grid = new Pixel * [rows];
        for (int i = 0; i < rows; i++)
            grid[i] = new Pixel[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                grid[i][j] = m.grid[i][j];

    }
    return *this;
}

Fractal& Fractal::operator=(Fractal&& m)
{
    cout << "> Move assignment operator called ..." << endl;
    if (this != &m)
    {
        swap(this->cols, m.cols);
        swap(this->rows, m.rows);
        swap(this->grid, m.grid);
    }
    return *this;
}

void saveToPPM(Fractal& F, const char* file)
{
    cout << "> Saving Fractal object to PPM file ..." << endl;
    ofstream output;
    output.open(file);
    output << "P3" << endl;
    output << F.cols << " " << F.rows << endl;
    output << F.maxIter << endl;

    for (int i = 0; i < F.rows; i++)
        for (int j = 0; j < F.cols; j++)
            output << F.grid[i][j] << " ";
    output << endl;

    output.close();

}


