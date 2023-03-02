#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include <randomprocess.h>

void RandomProcess::update() {
    double num = rp(0, 1);
    channel("link").send(num);
    cout << num << " ,";
}

double rp(double fmin, double fmax){
    double f = (double)rand() / double(RAND_MAX);
    return fmin + f * (fmax - fmin);
}