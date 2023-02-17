#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : real(x), imaginary(y) {}
    Complex(double a) : real(a), imaginary(0) {};

    double magnitude() const;
    double re() const;
    double im() const;
    Complex conjugate() const;
    

    private:
    double real, imaginary;
}; 

bool operator<(const Complex& a, const Complex& b);
bool operator==(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
Complex operator+(const Complex& a, const Complex& b);

#endif