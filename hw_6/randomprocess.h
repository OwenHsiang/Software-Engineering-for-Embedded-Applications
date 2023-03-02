#ifndef _RANDOMPROCESS_H
#define _RANDOMPROCESS_H
#include "elma/elma.h"
using namespace elma;
using namespace std;

class RandomProcess: public Process {

    public:
    RandomProcess(string name): Process(name) {}

    void init() {}
    void start() {}
    void update();  
    void stop() {}   
};  

double rp(double, double);

#endif