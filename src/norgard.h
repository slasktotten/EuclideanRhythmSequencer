//
//  norgard.h
//  infinityseries
//
//  Created by gustaf svenungsson on 27/01/2017.
//  Copyright © 2017 gustaf svenungsson. All rights reserved.
//

#ifndef norgard_h
#define norgard_h
#include <vector>



template<typename T>
std::vector<T> norgard(T _startingInterval, T _lengthOfTheSequence){
    std::vector<T> v;
    v.resize(_lengthOfTheSequence);
    v[0] = 0;
    v[1] = (_startingInterval);
    for (int i = 1; i < _lengthOfTheSequence/2; i++){
        T currentInterval = v[i]- v[i-1];
        v[2*i] =   v[2*i-2] - currentInterval;
        v[2*i+1] = v[2*i-1] + currentInterval;
    }
    return v;
}
#endif /* norgard_h */
