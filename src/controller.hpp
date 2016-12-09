//
//  controller.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 02/12/2016.
//
//

#ifndef controller_hpp
#define controller_hpp

#include <stdio.h>
#include <ofMain.h>
#include "ofParameterGroup.h"
#include "ofParameter.h"

class Controller {
public:
    Controller();
    void setup(string name);
    void draw();
    ofParameterGroup parameterGroup;
    ofParameter<int> nBeats;
    ofParameter<int> stepSize;
    ofParameter<int> offset;
};

#endif /* controller_hpp */
