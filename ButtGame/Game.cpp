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

#define GAME_INSET 50

Game::Game(int width, int height) {
	screenWidth_ = width;
	screenHeight_ = height;
	
	bounds_ = new GenericView(GAME_INSET, GAME_INSET, width - GAME_INSET * 2, height - GAME_INSET * 2, NULL);
	player_ = new Player(100,100, bounds_);
	
	for(int i = 0; i < 10; i++) {
		GenericEnemy* someButt = new GenericEnemy(rand() % (bounds_->width_ - kDefaultEnemySize), rand() % (bounds_->height_ - kDefaultEnemySize), bounds_);
		enemies_.push_back(someButt);
	}
}

Game::~Game() {
	
}

void Game::drawScreen() {
	//Calculate interpolation here
	al_clear_to_color(al_map_rgb(0,0,0));
	
	for(auto &view : views_) {
		view->draw();
	}
	
	for(auto &enemy : enemies_) {
		enemy->draw();
	}
	
	bounds_->draw();
	player_->draw();
	
	al_flip_display();
}

void Game::update() {
	player_->update();
	
	for(auto &enemy : enemies_) {
		enemy->update();
	}
}

void Game::handleInput(ALLEGRO_KEYBOARD_EVENT event) {
	player_->handleInput(event);
}