#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <string>

class Complex
{
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0);
    double getReal() const;
    double getImag() const;
    Complex operator+(const Complex &other) const;
    Complex operator-(const Complex &other) const;
    Complex operator*(const Complex &other) const;
    bool operator==(const Complex &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Complex &c);
    bool operator<(const Complex &other) const;
    bool operator>(const Complex &other) const;
};
namespace std
{
    string to_string(const Complex &c);
}

#endif // COMPLEX_HPP