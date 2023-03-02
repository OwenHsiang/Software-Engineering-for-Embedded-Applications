#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include "integrator.h"

void Integrator::start() {
     sum = 0.0;
}

void Integrator::update() {
    if (channel("link").nonempty()) {
        double lv = channel("link").latest();
        sum += lv * delta();
        cout << sum << " \n";
    }
}

double Integrator::value() {
    return sum;
}


