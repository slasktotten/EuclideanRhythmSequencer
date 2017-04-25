//
//  instrument.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 31/10/2016.
//
//

#include "instrument.hpp"

Instrument::Instrument(){}

void Instrument::noteOn(Cb _cb){
    callbackfunctions.push_back(_cb);
}

void Instrument::noteOn(Cb _cb, Cb _cb2){
    callbackfunctions.push_back(_cb);
    noteOff(_cb2);
}

void Instrument::noteOff(Cb _cb){
    callbackfunctions.push_back(_cb);
}