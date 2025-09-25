#ifndef TMR
#define TMR
#define TMR_TIME   0
#define TMR_ENERGY 1
#define TMR_ACTION 2

#include <iostream>
#if defined(TMR_VAR) && (TMR_VAR != TIME)
#warning "Included p3em.hpp"
#include "../p3em/C++/p3em.hpp"
#endif
#include <chrono>
using namespace std;
using namespace std::chrono;

class Tmr{
private:
  double zero=0.0, laps=0.0; // Zeros of the global metric
  double e0  =0.0, t0  =0.0;
#if !defined(TMR_VAR) || (TMR_VAR == TMR_TIME)
#warning "Using time"
  auto now(){ return duration<double,milli>(steady_clock::now().time_since_epoch()).count()*1.0E-3-t0; }
#elif TMR_VAR == TMR_ENERGY
#warning "Using Energy"
  p3em myem;
  auto now(){ return myem.getLatestValue()-e0; }
#elif TMR_VAR == TMR_ACTION
#warning "Using Action"
  p3em myem;
  auto now(){ return (myem.getLatestValue()-e0)*(duration<double,milli>(steady_clock::now().time_since_epoch()).count()*1.0E-3-t0); }
#endif

public:
#if defined(TMR_VAR) && (TMR_VAR != TMR_TIME)
  Tmr(): myem("../p3em.sh") {
    t0 = duration<double,milli>(steady_clock::now().time_since_epoch()).count()*1.0E-3;
    e0 = myem.getLatestValue();
  }
#endif
  void rst(){                  zero = 0.0;              laps = 0.0; }
  void pws(){ auto v=now(); if(zero>= 0.0) zero+=-v; if(laps>= 0.0) laps+=-v; }
  // TODO ?? purists may want to put error msg or asserts instead of `return -1. or -2.;` below.
  // I'd immediately spot a negative time.
  auto tot(){ auto v=now(); if(zero!= 0.0){ return   (zero>= 0.0)?v-zero:-zero;                     } return -1.; }
  auto lap(){ auto v=now(); if(laps!= 0.0){ auto x = (laps>= 0.0)?v-laps:-laps; laps = v; return x; } return -2.; }
  void tik(){ auto v=now(); if(zero<= 0.0) zero+= v; if(laps<= 0.0) laps+= v; }
#if !defined(TMR_VAR) || (TMR_VAR == TMR_TIME)
  auto tok(){ auto v=tot(); cout<<"Tot time/s: "<<v<<endl; return v; }
  auto tak(){ auto v=lap(); cout<<"Lap time/s: "<<v<<endl; return v; }
#elif TMR_VAR == TMR_ENERGY
  auto tok(){ auto v=tot(); cout<<"Tot energy/J: "<<v<<endl; return v; }
  auto tak(){ auto v=lap(); cout<<"Lap energy/J: "<<v<<endl; return v; }
#elif TMR_VAR == TMR_ACTION
  auto tok(){ auto v=tot(); cout<<"Tot action/Js: "<<v<<endl; return v; }
  auto tak(){ auto v=lap(); cout<<"Lap action/Js: "<<v<<endl; return v; }
#endif
};

#endif
