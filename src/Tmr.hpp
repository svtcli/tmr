#ifndef TMR
#define TMR

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Tmr{
  private:
    double zero=0.0, laps=0.0;
    auto now(){ return duration<double,milli>(steady_clock::now().time_since_epoch()).count()*1.0E-3; }
  public:
    void rst(){                  zero = 0.0;              laps = 0.0; }
    void pws(){ auto v=now(); if(zero>= 0.0) zero+=-v; if(laps>= 0.0) laps+=-v; }
    // TODO ?? purists may want to put error msg or asserts instead of `return -1. or -2.;` below.
    // I'd immediately spot a negative time.
    auto tot(){ auto v=now(); if(zero!= 0.0){ return   (zero>= 0.0)?v-zero:-zero;                     } return -1.; }
    auto lap(){ auto v=now(); if(laps!= 0.0){ auto x = (laps>= 0.0)?v-laps:-laps; laps = v; return x; } return -2.; }
    void tik(){ auto v=now(); if(zero<= 0.0) zero+= v; if(laps<= 0.0) laps+= v; }
    auto tok(){ auto v=tot(); cout<<"Tot time/s: "<<v<<endl; return v; }
    auto tak(){ auto v=lap(); cout<<"Lap time/s: "<<v<<endl; return v; }
};

#endif
