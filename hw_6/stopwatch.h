#ifndef _STOPWATCH_H
#define _STOPWATCH_H
#include "elma/elma.h"
#include <chrono>
using namespace elma;
using namespace std;

typedef chrono::duration<double,ratio<1,1>> seconds_type;

class Stopwatch {

    public:
    Stopwatch() {
        period = seconds_type::zero();
        status = 0;
    }

    void start();              // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    double get_minutes();      // number of minutes counted, as a double
    double get_seconds();      // number of seconds counted, as a double
    double get_milliseconds(); // number of milliseconds counted, as a double
    double get_nanoseconds();  // number of nanoseconds counted, as a double    

    private:
    high_resolution_clock::time_point st; //start time
    high_resolution_clock::time_point ed; //end time
    seconds_type period;
    int status;

};  

#endif