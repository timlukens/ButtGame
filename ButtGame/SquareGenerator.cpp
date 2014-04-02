//
//  SquareGenerator.cpp
//  ButtGame
//
//  Created by tim on 4/1/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SquareGenerator.h"
#include "math.h"

SquareGenerator::SquareGenerator(float frequency, float sampleRate) {
	frequency_ = frequency;
	sampleRate_ = sampleRate;
	increment_ = frequency_ * kTableSize / sampleRate_;
	
	vector<float> v;
	
	//odd harmonics with amp 1/harmonicNum
	for(int i = 1; i < kMaxHarmonics; i++) {
		if(i%2)
			v.push_back(1.f / (float)i);
		else
			v.push_back(0);
	}
		
	this->createBuffer(v);
	
	index_ = 0;
}

SquareGenerator::SquareGenerator() {
	buffer_.clear();
}

float SquareGenerator::tick() {
	return SignalGenerator::tick();
}