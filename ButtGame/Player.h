//
//  Player.h
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__Player__
#define __ButtGame__Player__

#include <iostream>
#include <allegro5/allegro.h>
#include "SquareView.h"
#include "GameDefines.h"
#include "GenericWeapon.h"

class Player {
	bool leftPressed_, rightPressed_, upPressed_, downPressed_;
	bool aPressed_, dPressed_, wPressed_, sPressed_;
	bool isAlive_;
	
	shared_ptr<SquareView> view_;
	shared_ptr<SquareView> hitBox_;
	shared_ptr<GenericView> parentView_;
	
	shared_ptr<GenericWeapon> weapon_;
	
public:
	Player(int x, int y, shared_ptr<GenericView> parentView);
	~Player();
    
	int get_x();
    int get_y();
    int get_width();
    int get_height();
	
	shared_ptr<GenericView> getView();
	shared_ptr<GenericView> getHitBox();
	shared_ptr<GenericWeapon> getWeapon();
	bool getIsAlive();
	
	void setIsAlive(bool isAlive);
	
	void handleInput(ALLEGRO_KEYBOARD_EVENT event);
	void update();
};

#endif /* defined(__ButtGame__Player__) */
