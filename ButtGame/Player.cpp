//
//  Player.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "Player.h"

Player::Player(int x, int y) {
	view_ = new SquareView(x, y, 100, 100, NULL);
}

void Player::draw() {
	view_->draw();
}

void Player::update() {
	int xVelocity = 0;
	int yVelocity = 0;
	
	if(leftPressed_) xVelocity -= X_SPEED;
	if(rightPressed_) xVelocity += X_SPEED;
	
	if(upPressed_) yVelocity -= Y_SPEED;
	if(downPressed_) yVelocity += Y_SPEED;
	
	view_->x_ += xVelocity;
	view_->y_ += yVelocity;
}

void Player::handleInput(ALLEGRO_KEYBOARD_EVENT event) {
	if(event.type == ALLEGRO_EVENT_KEY_DOWN) {		
		if(event.keycode == ALLEGRO_KEY_LEFT) leftPressed_ = true;
		if(event.keycode == ALLEGRO_KEY_RIGHT) rightPressed_ = true;
		if(event.keycode == ALLEGRO_KEY_UP) upPressed_ = true;
		if(event.keycode == ALLEGRO_KEY_DOWN) downPressed_ = true;
	}
	
	else if(event.type == ALLEGRO_EVENT_KEY_UP) {
		if(event.keycode == ALLEGRO_KEY_LEFT) leftPressed_ = false;
		if(event.keycode == ALLEGRO_KEY_RIGHT) rightPressed_ = false;
		if(event.keycode == ALLEGRO_KEY_UP) upPressed_ = false;
		if(event.keycode == ALLEGRO_KEY_DOWN) downPressed_ = false;
	}
}