#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include "stopwatch.h"

void Stopwatch::start() {
    st = high_resolution_clock::now();
    status = 1;
}

void Stopwatch::stop() {
    if (status == 0) return;
    ed = high_resolution_clock::now();
    period += ed - st;
    status = 0;
}

void Stopwatch::reset() {
    period = seconds_type::zero();
}

double Stopwatch::get_minutes() {
    typedef chrono::duration<double,ratio<60,1>> minutes_type;
    return minutes_type(period).count();  
}

double Stopwatch::get_seconds() {
    return period.count();
}

double Stopwatch::get_milliseconds() {
    typedef chrono::duration<double,milli> milliseconds_type;
    return milliseconds_type(period).count();
}

double Stopwatch::get_nanoseconds() {
    typedef chrono::duration<double,nano> nanoseconds_type;
    return nanoseconds_type(period).count();
}