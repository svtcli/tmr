
#include "../src/Tmr.hpp"  // to test
#include <unistd.h>   // for sleep
#include <cassert>    // for ASSERT

using namespace std;

template <typename F>
bool isclose(F value, F reference, F tolerance=3.0E-3){
  F expression = (reference > tolerance)?abs(reference/value-1.0):abs(reference-value);
  bool outcome = static_cast<bool>(expression <= tolerance);
#ifndef NDEBUG
  if(!outcome){
    cout<<"They are not close!"<<endl;
    cout<<"  Is value      "<<value     <<" ~= reference "<<reference<<"? If so, raise tolerance!"<<endl;
    cout<<"  Is expression "<<expression<<" ~< tolerance "<<tolerance<<"?"<<endl;
  }
#endif
  return outcome;
}

// Example usage
int main() {

#ifdef NDEBUG
    cout<<"Test won't work with NDEBUG defined! Recompile without it."<<endl; abort();
#endif

    Tmr sw;    bool out;
    cout<<endl<<"# Testing Tmr"<<endl;

    cout<<endl<<"## sleep 1, tok before tik"<<endl;
    sleep(1);
    assert(isclose(sw.tok(),0.0));

    cout<<endl<<"## Reset, sleep 100msec, tok  "<<endl;
    sw.rst(); sw.tik(); usleep(1E5);
    assert(isclose(sw.tok(), 1.0E-1));

    cout<<endl<<"## tik while already running, sleep 100msec, tok "<<endl; 
    sw.tik(); usleep(1E5);
    assert(isclose(sw.tok(), 2.0E-1));

    cout<<endl<<"## tik while already running, sleep 100msec, tok "<<endl; 
    sw.tik(); usleep(1E5);
    assert(isclose(sw.tok(), 3.0E-1));

    cout<<endl<<"## pws (pause), sleep 200msec, tok "<<endl;
    sw.pws(); usleep(2E5); auto tmp = sw.tok();
    assert(isclose(tmp, 3.0E-1));

    cout<<endl<<"## pws while already paused, sleep 100msec, tok "<<endl; 
    sw.pws(); usleep(1E5);
    assert(isclose(sw.tok(), tmp, 0.0)); //exact as above

    cout<<endl<<"## tik from paused, sleep 100msec, tok"<<endl;
    sw.tik(); usleep(1E5);
    assert( isclose(sw.tok(), 4.0E-1));

    cout<<endl<<"## tik again, sleep 300msec, tok"<<endl;
    sw.tik(); usleep(3E5);
    assert( isclose(sw.tok(), 7.0E-1));

    sw.rst(); sw.tik();


    double dt, sum;
    for(auto step=0; step<3; (++step) ){
      sum=0;
      for(auto seg=0; seg<4; ++seg){
        cout<<endl<<"## step "<<step<<" seg "<<seg;
        dt = seg/10.; usleep(dt*1.0E6); sum+=dt;
        assert(isclose(sw.seg(), dt) );
      }
      assert(isclose(sw.lap(),sum) );
    }
    cout<<endl;
    sw.log();

    cout<<endl<<"# All tests passed! :D "<<endl;

    return 0;
}
