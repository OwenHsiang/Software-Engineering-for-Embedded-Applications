#ifndef _FILTER_H
#define _FILTER_H
#include "elma/elma.h"
using namespace elma;
using namespace std;

class Filter: public Process {

    public:
    Filter(string name): Process(name) {}

    void init() {}
    void start();
    void update(); 
    void stop() {}  
    double value();

    private:
    double sum;
    double avg;
    int count;
    
};  

#endif