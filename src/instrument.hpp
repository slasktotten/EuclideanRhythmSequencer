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

typedef std::function<void ()> Cb;

class Instrument{
public:
    Instrument();
    void noteOn(Cb  _cb);
    void noteOn(Cb  _cb, Cb _cb2);
    void noteOff(Cb _cb);
    
    vector<Cb> callbackfunctions;
};



#endif /* instrument_hpp */
