//
//  Game.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "Game.h"
#include "SquareView.h"
#include <allegro5/allegro_primitives.h>

Game::Game(int width, int height) {
	screenWidth_ = width;
	screenHeight_ = height;
	
	SquareView* square = new SquareView(10,10,50,50, NULL);
	views_.push_back(square);
	
	player_ = new Player(100,100);
}

Game::~Game() {
	
}

void Game::drawScreen() {
	//Calculate interpolation here
	al_clear_to_color(al_map_rgb(50,123,1));
	
	for(auto &view : views_) {
		view->draw();
	}
	
	player_->draw();
	
	al_flip_display();
}

void Game::update() {
	player_->update();
}

void Game::handleInput(ALLEGRO_KEYBOARD_EVENT event) {
	player_->handleInput(event);
}