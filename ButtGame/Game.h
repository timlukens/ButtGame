//
//  Game.h
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__Game__
#define __ButtGame__Game__

#include <iostream>
#include <allegro5/allegro.h>
#include <vector>
#include "GenericView.h"

using namespace std;

class Game {
	ALLEGRO_DISPLAY* gameDisplay_;
	
	vector<GenericView*> views_;
	
	int screenWidth_;
	int screenHeight_;
	
	bool aDown_, sDown_, dDown_, fDown_;
	bool leftDown_, rightDown_, upDown_, downDown_;
	
public:
	Game(int width, int height);
	~Game();
	
	void update();
	void drawScreen();
	void handleInput(ALLEGRO_KEYBOARD_EVENT event);
};

#endif /* defined(__ButtGame__Game__) */
