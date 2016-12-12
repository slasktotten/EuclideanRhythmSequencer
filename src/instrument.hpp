//
//  instrument.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 31/10/2016.
//
//

#ifndef instrument_hpp
#define instrument_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxMaxim.h"
class Instrument{
public:
    Instrument();
    void on();
    void off();
    void output(double _input);
    double signal;
    double amp;
    void signal_processing();
};



#endif /* instrument_hpp */
