//
//  delay.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 03/11/2016.
//
//

#include "delay.hpp"
myDelay::myDelay(){
    readIndex  = 0;
    writeIndex = 0;
    delaySeconds = 0.5; //this parameter needs to be set in the constructor
    decay = 0.5;
    delayBuffer.resize(88200);
}


//based of delayline code provided by Simon Katan in Audio Visual Programming
double myDelay::slapback(double signal){
    readIndex = writeIndex - int(delaySeconds * 44100);
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = signal;
     writeIndex = ++writeIndex % delayBuffer.size();
    return signal + delayBuffer[readIndex];
}

double myDelay::echo(double signal){
    readIndex = writeIndex - int(delaySeconds * 44100);
    if(readIndex < 0) readIndex += delayBuffer.size();
    delayBuffer[writeIndex] = signal + delayBuffer[readIndex] * decay;
    writeIndex = ++writeIndex % delayBuffer.size();
    return signal + delayBuffer[readIndex];
}

