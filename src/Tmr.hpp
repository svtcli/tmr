#ifndef TMR
#define TMR

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef MPI
#include <MPI.h>
#include <unistd.h>
#endif

using namespace std;
using namespace std::chrono;

class Tmr{

  private:
    size_t segI = 0  , lapI = 0  ;
    double tim0 = 0.0, seg0 = 0.0;
    std::vector<double> segV, lapV;
    inline auto now(){ return duration<double,milli>(high_resolution_clock::now().time_since_epoch()).count()*1.0E-3; }
    inline double alg(double xx){ return (!pwsd()) ? (now()-xx) : (-xx); }
    inline bool pwsd(){ return (tim0<=0.); }

  public:
    Tmr(){ segV.push_back(0.0); lapV.push_back(0.); }
    inline void tik( ) { if( pwsd()){ tim0+= now(); seg0+= now();}; }
    inline void pws( ) { if(!pwsd()){ tim0-= now(); seg0-= now();}; }
    inline void rst( ) { tim0 = 0.0  ; seg0 = 0.0  ; segI=0; } // but keeps segments and laps!

    inline double tok(){return alg(tim0); }
    inline double seg(){auto xx=alg(seg0)   ; if(!pwsd()){segV[segI++]+=xx; lapV[lapI]+=xx; seg0=now(); if(!lapI)segV.push_back(0.); }; return xx;}
    inline double lap(){auto xx=lapV[lapI++]; if(!pwsd()){     segI=0;                                           lapV.push_back(0.); }; return xx;}
    void log(){
      double mean, max, min; size_t iMax, iMin;
#ifdef MPI
#else
      size_t rank = 0, size=1;
#endif
      if(!rank){
        cout<<"Load imbalance across laps by ranks:"<<std::endl;
        cout<<"Rank\tmean\t\tiMin: min\t\tmax: iMax"<<endl;
      }
      iMax = max_element(lapV.begin(),lapV.end()-1   ) - lapV.begin();
      iMin = min_element(lapV.begin(),lapV.end()-1   ) - lapV.begin();
      mean = accumulate (lapV.begin(),lapV.end()-1,.0) /(lapV.size()-1);
      for(auto i = 0; i < size; ++i)
       if(!(rank-i)){
#ifdef MPI
         usleep(i*300);
#endif
         cout <<i<<"\t"<<mean<<"\t"<<iMin<<": "<<lapV[iMin]<<"\t\t"<<iMax<<": "<<lapV[iMax]<<endl;
       }

      if(!rank){
        cout<<"Load imbalance across segments by ranks:"<<std::endl;
        cout<<"Rank\tmean\t\tiMin: min\t\tmax: iMax"<<endl;
      }
      iMax = max_element(segV.begin(),segV.end()-1   ) - segV.begin();
      iMin = min_element(segV.begin(),segV.end()-1   ) - segV.begin();
      mean = accumulate (segV.begin(),segV.end()-1,.0) /(segV.size()-1);
      for(auto i = 0; i < size; ++i)
       if(!(rank-i)){
#ifdef MPI
         usleep(i*300);
#endif
         cout <<i<<"\t"<<mean<<"\t"<<iMin<<": "<<segV[iMin]<<"\t\t"<<iMax<<": "<<segV[iMax]<<endl;
       }
    }

};

#endif
