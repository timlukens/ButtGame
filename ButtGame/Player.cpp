//
//  Player.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "Player.h"
#include "Game.h"

#define X_SPEED 640.f / LOGIC_FPS
#define Y_SPEED 640.f / LOGIC_FPS

Player::Player(int x, int y, GenericView* parentView) {
	parentView_ = parentView;
	view_ = new SquareView(x, y, 100, 100, parentView);
	
	leftPressed_ = false;
	rightPressed_ = false;
	upPressed_ = false;
	downPressed_ = false;
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
	
	//find the actual x,y coordinates inside the parentView
	int x = view_->x_;
	int y = view_->y_;
	parentView_->mapCoordinatesToParentView(x, y);
	
	//make sure we're still in bounds
	if(x + xVelocity > parentView_->x_ && x + view_->width_ + xVelocity < parentView_->x_ + parentView_->width_)
		view_->x_ += xVelocity;
	
	if(y + yVelocity > parentView_->y_ && y + view_->height_ + yVelocity < parentView_->y_ + parentView_->height_)
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