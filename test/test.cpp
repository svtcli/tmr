#include "../src/Tmr.hpp"  // to test
#include <unistd.h>   // for sleep
#include <cassert>    // for ASSERT

using namespace std;

template <typename F>
bool isclose(F value, F reference, F tolerance=2.0E-2){ // default tolerance is 2%
#if defined(TMR_VAR) && (TMR_VAR != TMR_TIME)
#ifndef NDEBUG
  cout<<"- WARNING: Tests for energy ill-defined. Check always passes by design."<<endl;
#endif
  return true;
#else
  F expression = (reference > tolerance)?abs(reference/value-1.0):abs(reference-value);
  bool outcome = static_cast<bool>(expression <= tolerance);
#ifndef NDEBUG
  if(!outcome){
    cout<<"They are not close!"<<endl;
    cout<<"  Is value      "<<value     <<" ~= reference "<<reference<<"? If so, raise tolerance!"<<endl;
    cout<<"  Is expression "<<expression<<" <= tolerance "<<tolerance<<"?"<<endl;
  }
#endif
  return outcome;
#endif
}

// Example usage
int main() {

#ifdef NDEBUG
 cout<< "Tests won't work well with NDEBUG defined! Recompile without it."<<endl; abort();
#endif

    Tmr sw;    bool out;
    cout<<endl<<"# Testing Tmr"<<endl;

    cout<<endl<<"## sleep 1, tok before tik"<<endl;
    usleep(1E5);
    assert(isclose(sw.tok(),-1.0));

    cout<<endl<<"## sleep 100msec, tak (=print lap) before tik"<<endl;
    usleep(1E5);
    assert(isclose(sw.tak(), -2.0));

    cout<<endl<<"## Reset, tik, tok."<<endl;
    sw.rst(); sw.tik();
    assert(isclose(sw.tok(), 0.0));

    cout<<endl<<"## Sleep 100msec, tok  "<<endl;
    usleep(1E5);
    assert(isclose(sw.tok(), 1.0E-1));

    cout<<endl<<"## tik while already running, sleep 100msec, tok "<<endl;
    sw.tik(); usleep(1E5);
    assert(isclose(sw.tok(), 2.0E-1));

    cout<<endl<<"## tik while already running, sleep 100msec, tot "<<endl;
    sw.tik(); usleep(1E5);
    assert(isclose(sw.tot(), 3.0E-1));

    cout<<endl<<"## pws (pause), sleep 100msec, tot "<<endl;
    sw.pws(); usleep(1E5); auto tmp = sw.tot(); // save it for later
    assert(isclose(tmp, 3.0E-1));

    cout<<endl<<"## pws while already paused, sleep 100msec, tot "<<endl;
    sw.pws(); usleep(1E5);
    assert(isclose(sw.tot(), tmp, 0.0)); //exact as above

    cout<<endl<<"## tik from paused, sleep 100msec, tot"<<endl;
    sw.tik(); usleep(1E5);
    assert( isclose(sw.tot(), 4.0E-1));

    cout<<endl<<"## print first lap, should be same as tot "<<endl;
    assert( isclose(sw.lap(), 4.0E-1));

    cout<<endl<<"## sleep 200msec, print next lap "<<endl;
    usleep(2.0E5);
    assert( isclose(sw.lap(), 2.0E-1));

    cout<<endl<<"## pws, sleep 200msec, print next lap "<<endl;
    sw.pws(); usleep(2.0E5);
    assert( isclose(sw.lap(), 0.0));

    cout<<endl<<"## restart with tik, sleep 120msec, tak "<<endl;
    sw.tik(); usleep(1.2E5);
    assert( isclose(sw.tak(), 1.2E-1));

    cout<<endl<<"## usleep 120msec again, tak again "<<endl;
    usleep(1.2E5);
    assert( isclose(sw.tak(), 1.2E-1));

    cout<<endl<<"## just tok "<<endl;
    assert( isclose(sw.tok(), 8.4E-1));

    cout<<endl<<"## a second tok "<<endl;
    assert( isclose(sw.tok(), 8.4E-1));

    cout<<endl<<"## 4x tak "<<endl;
    assert( isclose(sw.tak(),0.0));
    assert( isclose(sw.tak(),0.0));
    assert( isclose(sw.tak(),0.0));
    assert( isclose(sw.tak(),0.0));

    cout<<endl<<"## reset, NO tik, then tok "<<endl;
    sw.rst();
    assert( isclose(sw.tok(),-1.0));

    cout<<endl<<"## reset,    tik, then tok "<<endl;
    sw.rst();   sw.tik();
    assert( isclose(sw.tok(),0.0));

    cout<<endl<<"## sleep 200msec, tok "<<endl;
    usleep(2.0E5);
    assert( isclose(sw.tok(),2.0E-1));

    cout<<endl<<"# All tests passed! :D "<<endl;

    return 0;
}
