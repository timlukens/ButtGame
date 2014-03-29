//
//  Sine.cpp
//  ButtGame
//
//  Created by tim on 3/29/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "Sine.h"
#include "math.h"

Sine::Sine(float frequency, float sampleRate) {
	frequency_ = frequency;
	sampleRate_ = sampleRate;
	increment_ = frequency_ * kTableSize / sampleRate_;
	
	for(int i = 0; i < kTableSize; i++)
		buffer_.push_back(sin((2.f * M_PI * i) / kTableSize));
	
	index_ = 0;
}

Sine::~Sine() {
	buffer_.clear();
}

float Sine::tick() {
	float output = buffer_[(int)index_];
	index_ += increment_;
	if(index_ >= kTableSize)
		index_ -= kTableSize;
	
	return output;
}

void Sine::setFrequency(float freq) {
	frequency_ = freq;
}