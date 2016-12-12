//
//  euclideanRhythm.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 12/11/2016.
//
//

#include "euclideanRhythm.hpp"

EuclideanRhythm::EuclideanRhythm(){
    sizeOfSeq = 16;
}

void EuclideanRhythm::it(int step, int pulse){
    sizeOfSeq = step;
    remainder.resize(step);
    count.resize(step);
    for (int i = 0; i < step; i++) sequence.push_back(false);
    if (pulse > step) pulse = step;
    int divisor = step - pulse;
    remainder[0] = pulse;
    index = 0;
    do {
        count[index] = divisor / remainder[index];
        remainder[index+1] = divisor % remainder[index];
        divisor = remainder[index];
        index++;
    }
    while(remainder[index] > 0);
    count[index] = divisor;
    buildSeq(index);
    for (int i = sequence.size(); i > 0; i--){
        slots.push_back(sequence[i-1]);
    }
}

void EuclideanRhythm::buildSeq(int index){
    cout << index << endl;
    if (index == -1) {
        sequence[step] = false;
        step           = step +1;
    }
    else if (index == -2){
        sequence[step] = true;
        step = step + 1;
    }
    else{
        for (int i =0; i < count[index]; i++)
            buildSeq(index-1);
        if(remainder[index] !=0)
            buildSeq(index-2);
    }
}

const vector<bool> EuclideanRhythm::getSequence()
{
    return slots;
}

//int EuclideanRhythm::getSequence(int index){
//    return slots[index];
//}