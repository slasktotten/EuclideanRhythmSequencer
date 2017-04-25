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
  virtual void setup(string name);
    
    ofParameterGroup parameterGroup;
    ofParameter<int> nBeats;
    ofParameter<int> stepSize;
    ofParameter<int> offset;
    ofParameter<int> subdivision;

    
};

//-----------------------------------------------------------------//

class NoteController : public Controller {
public:
    NoteController();
    void setup(string name);
    ofParameter<int> arpeggioType;
    ofParameter<int> note;
};




#endif /* controller_hpp */
