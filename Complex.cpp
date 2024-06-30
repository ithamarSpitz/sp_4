#include "Complex.hpp"
#include <sstream>

Complex::Complex(double r, double i) : real(r), imag(i) {}

double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }

Complex Complex::operator+(const Complex &other) const
{
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex &other) const
{
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex &other) const
{
    return Complex(real * other.real - imag * other.imag,
                   real * other.imag + imag * other.real);
}

bool Complex::operator==(const Complex &other) const
{
    return (real == other.real) && (imag == other.imag);
}

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    os << c.real;
    if (c.imag >= 0)
        os << "+";
    os << c.imag << "i";
    return os;
}

bool Complex::operator<(const Complex &other) const
{
    return real * real + imag * imag < other.real * other.real + other.imag * other.imag;
}

bool Complex::operator>(const Complex &other) const
{
    return other < *this;
}

namespace std
{
    string to_string(const Complex &c)
    {
        std::ostringstream oss;
        oss << c; // This uses the existing operator<< overload
        return oss.str();
    }
}