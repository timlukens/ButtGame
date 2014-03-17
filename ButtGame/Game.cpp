//
//  Game.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "Game.h"
#include "SquareView.h"

Game::Game(int width, int height) {
	screenWidth_ = width;
	screenHeight_ = height;
	
	gameDisplay_ = al_create_display(width, height);
	
	SquareView* square = new SquareView(10,10,50,50, gameDisplay_);
	views_.push_back((GenericView*)square);
	
	aDown_ = false;
}

Game::~Game() {
	
}

void Game::drawScreen() {
	//Calculate interpolation here
	if(aDown_) {
		al_clear_to_color(al_map_rgb(128, 0, 0));
	} else {
		al_clear_to_color(al_map_rgb(50,123,1));
	}
	
	for(auto &view : views_) {
		view->draw();
	}
	
	al_flip_display();
}

void Game::update() {
	
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