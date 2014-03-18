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
#include "Player.h"

#define GAME_WIDTH 1024
#define GAME_HEIGHT 768
#define LOGIC_FPS 128.f
#define INPUT_FPS 1280.f

using namespace std;

class Game {	
	vector<GenericView*> views_;
	
	int screenWidth_;
	int screenHeight_;
	
	GenericView* bounds_;
	
	Player* player_;
	
public:
	Game(int width, int height);
	~Game();
	
	void update();
	void drawScreen();
	void handleInput(ALLEGRO_KEYBOARD_EVENT event);
};

#endif /* defined(__ButtGame__Game__) */
