//
//  reverb.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 21/11/2016.
//
//

#ifndef reverb_hpp
#define reverb_hpp
#define REVERB_BUFFER_LEN 8000

#include <stdio.h>
#include "ofMain.h"
#include "ofxMaxim.h"


class Reverb{
public:
    int delayMilliseconds;
    int delaySamples;
    int bufferSize;
    float decay;
    void reverb( int16_t* Buffer, int N);
    double signal, output;
    double run(double _signal);
    vector<double> buffer;
    Reverb(int _bufferSize);
};

#endif /* reverb_hpp */
