#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include "filter.h"

void Filter::start() {
     sum = 0.0;
     avg = 0.0;
     count = 0;
}

void Filter::update() {
    if ( channel("link").nonempty() ) {
        double lv = channel("link").latest(); //latest value
        if (count < 10) {
            avg = (avg * count + lv) / (count + 1);
            count++;
        }
        else {
            avg = avg + (lv - channel("link", count - 10));
        }
    }
}

double Filter::value() {
    return avg;
}


