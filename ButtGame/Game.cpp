//
//  Game.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "Game.h"

Game::Game(int width, int height) {
	screenWidth_ = width;
	screenHeight_ = height;
	
	aDown_ = false;
}

Game::~Game() {
	
}

void Game::update() {
	if(aDown_) {
		cout << "A down" << endl;
	}
}

void Game::handleInput(ALLEGRO_KEYBOARD_EVENT event) {
	if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
		aDown_ = event.keycode == ALLEGRO_KEY_A;
		sDown_ = event.keycode == ALLEGRO_KEY_S;
		dDown_ = event.keycode == ALLEGRO_KEY_D;
		fDown_ = event.keycode == ALLEGRO_KEY_F;
		
		leftDown_ = event.keycode == ALLEGRO_KEY_LEFT;
		rightDown_ = event.keycode == ALLEGRO_KEY_RIGHT;
		upDown_ = event.keycode == ALLEGRO_KEY_UP;
		downDown_ = event.keycode == ALLEGRO_KEY_DOWN;
	}
	
	else if(event.type == ALLEGRO_EVENT_KEY_UP) {
		aDown_ = false;
	}
}