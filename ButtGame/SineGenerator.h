//
//  Sine.h
//  ButtGame
//
//  Created by tim on 3/29/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__Sine__
#define __ButtGame__Sine__

#include <iostream>
#include <vector>
#include "SignalGenerator.h"
#include "GameDefines.h"

using namespace std;

class SineGenerator : public SignalGenerator {
	
public:
	SineGenerator(float frequency = 1.f, float sampleRate = LOGIC_FPS);
	SineGenerator();
	
	float tick();
};

#endif /* defined(__ButtGame__Sine__) */
