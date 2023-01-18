#include <math.h>
#include "complex.h"

Complex add(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real + c2.real;
    result.im = c1.im + c2.im;
    return result;
}

Complex negate(Complex c1) {
    Complex result;
    result.real = -c1.real;
    result.im = -c1.im;
    return result;
}

Complex multiply(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real*c2.real - c1.im*c2.im;
    result.im = c1.im*c2.real + c2.im*c1.real;
    return result;
}

double magnitude(Complex c1) {
    double result = sqrt(pow(c1.real, 2)+pow(c1.im, 2));
    return result;
}