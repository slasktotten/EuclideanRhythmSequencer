//
//  reverb.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 21/11/2016.
//
//

#include "reverb.hpp"


Reverb::Reverb(int _bufferSize) : bufferSize(_bufferSize){
    delayMilliseconds = 500;
    delaySamples = (int)((float)delayMilliseconds * 44.1f);
    decay = 0.5;
}


//vector input
//double Reverb::run(double _signal){
//    cout << 88200 - delaySamples<< endl;
//    for (int i = 0; i < 44100 - delaySamples; i++)
//    {
//        // WARNING: overflow potential
//        buffer[i] = _signal;
//        buffer[i + delaySamples] += (double)(buffer[i] * decay);
//        output = buffer[i + delaySamples];
//        cout << output << endl;
//        return output;
//    }
//}
//



void Reverb::reverb( int16_t* Buffer, int N)
{
    int i;
    float decay = 0.5f;
    cout << Buffer << endl;
    static int16_t sampleBuffer[REVERB_BUFFER_LEN] = {0};
    
    //Make room at the end of buffer to append new samples
    for (i = 0; i < REVERB_BUFFER_LEN - N; i++)
        sampleBuffer[ i ] = sampleBuffer[ i + N ] ;
    
    //copy new chunk of audio samples at the end of buffer
    for (i = 0; i < N; i++)
        sampleBuffer[REVERB_BUFFER_LEN - N + i ] = Buffer[ i ] ;
    
    //perform effect
    for (i = 0; i < REVERB_BUFFER_LEN - 1600; i++)
    {
        if((i + 1600) >= REVERB_BUFFER_LEN - N)
            sampleBuffer[i + 1600] += (int16_t)((float)sampleBuffer[i] * decay);
    }
    //copy output sample
    for (i = 0; i < N; i++)
        Buffer[ i ] = sampleBuffer[REVERB_BUFFER_LEN - N + i ];
    
    
}
