//
//  euclideanRhythm.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 12/11/2016.
//
//

#ifndef euclideanRhythm_hpp
#define euclideanRhythm_hpp

#include <stdio.h>
#include "ofMain.h"

class EuclideanRhythm{
    
public:
    EuclideanRhythm();
    void it(int step, int pulse);
    void buildSeq(int index);
//    int getSequence(int index);
    const vector<bool> getSequence();
    int getSize();
    
private:
    vector<bool>sequence;
    vector<bool>slots;
    vector<int>remainder;
    vector<int>count;
    
    int sizeOfSeq;
    int index;
    int step;
};



#endif /* euclideanRhythm_hpp */
