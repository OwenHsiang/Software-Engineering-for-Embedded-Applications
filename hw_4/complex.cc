#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(real*real + imaginary*imaginary);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

double Complex::re() const {
    return real;
}

double Complex::im() const {
    return imaginary;
}

Complex Complex::conjugate() const {
    return Complex(real, -imaginary);
}

Complex operator*(const Complex& a, const Complex& b) {
    return  Complex(a.re() * b.re() - a.im() * b.im(), a.re() * b.im() + a.im() * b.re());
}

Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.re() + b.re(), a.im() + b.im());
}

bool operator==(const Complex& a, const Complex& b)
{
    return (a.im() == b.im() && a.re() == b.re());
}