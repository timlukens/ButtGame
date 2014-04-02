//
//  SignalGenerator.cpp
//  ButtGame
//
//  Created by tim on 3/29/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SignalGenerator.h"
#include "math.h"
#include "GameDefines.h"

SignalGenerator::SignalGenerator() {
	frequency_ = 440.f;
	index_ = 0.f;
	sampleRate_ = LOGIC_FPS;
	increment_ = frequency_ * kTableSize / sampleRate_;
}

SignalGenerator::~SignalGenerator() {
	buffer_.clear();
}

float SignalGenerator::tick() {
	float output = buffer_[(int)index_];
	index_ += increment_;
	if(index_ >= kTableSize)
		index_ -= kTableSize;
	
	return output;
}

void SignalGenerator::setSampleRate(float sampleRate) {
	sampleRate_ = sampleRate;
}

float SignalGenerator::getSampeRate() {
	return sampleRate_;
}

void SignalGenerator::setFrequency(float freq) {
	frequency_ = freq;
	increment_ = frequency_ * kTableSize / sampleRate_;
	index_ = 0;
}

float SignalGenerator::getFrequency() {
	return frequency_;
}

void SignalGenerator::createBuffer(vector<float> amplitudes) {
	//first zero out the buffer
	for(int i = 0; i < kTableSize; i++) {
		buffer_.push_back(0);
	}
	
	//now create a buffer with sum of sines, each sine being a harmonic
	float scaler = 0;
	for(int i = 0; i < kTableSize; i++) {
		scaler = 0;
		for(int j = 0; j < amplitudes.size(); j++) {
			buffer_[i] += (sin((2.0*M_PI*i/kTableSize)*(j+1))) * amplitudes[j];
			scaler += amplitudes[j];
		}
		
		if(amplitudes.size() > 1) buffer_[i] /= (scaler - 1);
	}
}

void SignalGenerator::setBuffer(vector<float> buffer) {
	buffer_ = buffer;
}