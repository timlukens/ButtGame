//
//  SquareGenerator.h
//  ButtGame
//
//  Created by tim on 4/1/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__SquareGenerator__
#define __ButtGame__SquareGenerator__

#include <iostream>
#include <vector>
#include "SignalGenerator.h"
#include "GameDefines.h"

using namespace std;

class SquareGenerator : public SignalGenerator {
	
public:
	SquareGenerator(float frequency = 1.f, float sampleRate = LOGIC_FPS);
	SquareGenerator();
	
	float tick();
};

#endif /* defined(__ButtGame__SquareGenerator__) */
