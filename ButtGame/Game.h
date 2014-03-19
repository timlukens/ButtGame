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
#include <memory>
#include "GenericView.h"
#include "GenericEnemy.h"
#include "Player.h"
#include "GameDefines.h"

using namespace std;

class Game {
	Game() {};
	Game(int width, int height);
	Game(Game const&);
//	Game& operator=(Game const&){};	//wtf copy constructor
	static Game* m_pInstance;
	
	vector<shared_ptr<GenericView> > views_;
	vector<shared_ptr<GenericEnemy> > enemies_;
//	vector<GenericEnemy*> enemies_;
	
	ALLEGRO_BITMAP* bitmapBuffer_;
	
	int scaleW_, scaleH_, scaleX_, scaleY_;
	
	int screenWidth_;
	int screenHeight_;
	
	shared_ptr<GenericView> bounds_;
	
	unique_ptr<Player> player_;
	
public:
    bool isGameRunning;
	static Game* instance();
	~Game();
	void update();
	void drawScreen();
	void handleInput(ALLEGRO_KEYBOARD_EVENT event);
};

#endif /* defined(__ButtGame__Game__) */
