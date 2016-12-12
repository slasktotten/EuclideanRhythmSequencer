//
//  instrument.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 31/10/2016.
//
//

#include "instrument.hpp"

Instrument::Instrument(){
    
}



void Instrument::output(double _input){
    signal  = _input;
}

void Instrument::signal_processing(){
    /*
     do dsp stuff to signal in here
     */
}


/*
 I need an array of oscillators to be able to pass through the instrument class
 Inside the Instrument class I need to be able to process the signal through effects, filters and other dsp stuff
 
 */