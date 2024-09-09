#include "Complex.hpp"

Complex::Complex() :real(0.0), imag(0.0) {}
Complex::Complex(const Complex& a) :real(a.real), imag(a.imag) {}
Complex::Complex(double a) :real(a), imag(0.0) {}
Complex::Complex(double a, double b) :real(a), imag(b) {}
Complex::~Complex() {}

double& Complex:: operator [](const char* a)
{
	if (a == "real")
		return this->real;
	else if (a == "imaginary" || a == "imag")
		return this->imag;
	else
		throw InputOutOfBoundsException("Error!", a);
}

const Complex operator*(const Complex& a, const Complex& b)
{
	Complex c;
	try
	{
		c["real"] = a.real * b.real - a.imag * b.imag;
		c["imag"] = a.real * b.imag + a.imag * b.real;
	}
	catch (Pixel::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	catch (Complex::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	return c;
}

const Complex operator/(const Complex& a, const Complex& b)
{
	Complex c;
	try
	{
		c["real"] = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag);
		c["imag"] = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag);
	}
	catch (Pixel::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	catch (Complex::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	return c;
}

const Complex operator+(const Complex& a, const Complex& b)
{
	Complex c;
	try
	{
		c["real"] = a.real + b.real;
		c["imag"] = a.imag + b.imag;
	}
	catch (Pixel::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	catch (Complex::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	return c;
}

const Complex operator-(const Complex& a, const Complex& b)
{
	Complex c;
	try
	{
		c["real"] = a.real - b.real;
		c["imag"] = a.imag - b.imag;
	}
	catch (Pixel::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	catch (Complex::InputOutOfBoundsException e)
	{
		cout << e.returnError();
		cout << e.returnOffendingIndex();
	}
	return c;
}

double getMagnitude(const Complex& a)
{
	return a.real * a.real + a.imag * a.imag;
}

Complex::InputOutOfBoundsException::InputOutOfBoundsException(const char* em, const char* oi)
{
	this->errorMessage = em;
	this->offendingIndex = oi;
}

const char* Complex::InputOutOfBoundsException::returnError()
{
	return errorMessage;
}

const char* Complex::InputOutOfBoundsException::returnOffendingIndex()
{
	return offendingIndex;
}