//
//  delay.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 03/11/2016.
//
//

#ifndef delay_hpp
#define delay_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxMaxim.h"

class myDelay {
public:
    vector<double> delayBuffer;
    double delaySeconds;
    double slapback(double signal);
    double echo(double signal);
    int readIndex, writeIndex;
    float decay;
    myDelay();
};


#endif /* delay_hpp */
