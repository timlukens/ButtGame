//
//  SignalGenerator.h
//  ButtGame
//
//  Created by tim on 3/29/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__SignalGenerator__
#define __ButtGame__SignalGenerator__

#include <iostream>
#include <vector>

using namespace std;

#define kTableSize 256.f
#define kMaxHarmonics 30

class SignalGenerator {
protected:
	virtual float tick();
	
	vector<float> buffer_;
	float frequency_;
	float increment_;
	float sampleRate_;
	float index_;
	
public:
	SignalGenerator();
	~SignalGenerator();
	
	void setSampleRate(float sampleRate);
	float getSampeRate();
	void setFrequency(float freq);
	float getFrequency();
	
	void createBuffer(vector<float> amplitudes);
	void setBuffer(vector<float> buffer);
};

#endif /* defined(__ButtGame__SignalGenerator__) */
