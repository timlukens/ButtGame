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

#define kPlayerSize 25

class Player {
	bool leftPressed_, rightPressed_, upPressed_, downPressed_;
	unique_ptr<SquareView> view_;
	shared_ptr<GenericView> parentView_;
	
public:
	Player(int x, int y, shared_ptr<GenericView> parentView);
	~Player();
    SquareView* get_view();
    void handleInput(ALLEGRO_KEYBOARD_EVENT event);
	void update();
	void draw();
};

#endif /* defined(__ButtGame__Player__) */
