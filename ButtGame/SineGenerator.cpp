//
//  Sine.cpp
//  ButtGame
//
//  Created by tim on 3/29/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SineGenerator.h"
#include "math.h"

SineGenerator::SineGenerator(float frequency, float sampleRate) {
	frequency_ = frequency;
	sampleRate_ = sampleRate;
	increment_ = frequency_ * kTableSize / sampleRate_;
	
	vector<float> v;
	v.push_back(1);
	this->createBuffer(v);
	
	index_ = 0;
}

SineGenerator::SineGenerator() {
	buffer_.clear();
}

float SineGenerator::tick() {
	return SignalGenerator::tick();
}