//
//  oscilllator.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 20/10/2016.
//
//

#include "oscilllator.hpp"
Oscil::Oscil(){}

double Oscil::signal(string wType){
        if (wType == "sine")     return env.adsr(osc.sinewave(freq), env.trigger)  * amp;
        if (wType == "square")   return env.adsr(osc.square(freq), env.trigger)    * amp;
        if (wType == "triangle") return env.adsr(osc.triangle(freq), env.trigger)  * amp;
        return NULL;
}

void Oscil::setAmp(double a){
    amp  = a;
}
void Oscil::setFreq(double f){
    freq = f;
}

void Oscil::on(){
    env.trigger = 1;
}

void Oscil::off(){
    env.trigger = 0;
}

void Oscil::setEnv(double a, double d, double s, double r){
    env.setAttack(a);
    env.setDecay(d);
    env.setSustain(s);
    env.setRelease(r);
}

//-----------------------------------------------------------------------//
Carrier::Carrier (double _f, double _modSignal, double _a): Oscil(), f(_f), modSignal(_modSignal),a(_a)
{
    freq = _f + modSignal;
    amp  = _a;
}

void Carrier::setFreq(double f, double fm){
    freq = f + fm;
}

void Carrier::setAmp(double a, double am){
    amp  = a + am;
}

void Carrier::callbackTest(double _n, double _j){
    test = _n + _j;
}

//-----------------------------------------------------------------------//

double FM::signal(string _wType, double _offset, double _f){
    if(_wType == "sine")      return osc.sinewave(_f) * _offset;
    if(_wType == "square")    return osc.square  (_f) * _offset;
    if(_wType == "triangle")  return osc.triangle(_f) * _offset;
    return NULL;
}