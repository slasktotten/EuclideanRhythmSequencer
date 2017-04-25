//
//  oscilllator.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 20/10/2016.
//
//

#ifndef oscilllator_hpp
#define oscilllator_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxMaxim.h"
//turn into an abstract base class


class Oscil
{
public:
    Oscil();
    maxiOsc osc;
    maxiEnv env;
    void     on();
    void     off();
    void     setAmp (double a);
    void     setFreq(double f);
    void     setEnv(double a, double d, double s, double r);
    double   signal(string wType);
    double   amp, freq;
    private :
};

//-----------------------------------------------------------------//

class Carrier : public Oscil {
    public :
    using Oscil::setAmp; //override parent method to allow modulation
    using Oscil::setFreq; //override parent method to allow for modulation
    
    Carrier(double _f, double _modSignal, double _a);
    void setFreq(double f, double fm);
    void setAmp(double f, double am);
    void callbackTest(double _n, double _j);
    double f, a, modSignal;
    int test;
};

//-----------------------------------------------------------------//

class FM : public Oscil {
public:
    double signal(string _wType, double _offset, double _f);
//    freq   = rate of modulation
//    offset = amount of modulation, i.e. target frequency
//    modulation should be higher than carrier signal
};
#endif /* oscilllator_hpp */
