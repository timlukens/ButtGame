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
#include <thread>
#include <mutex>
#include <Box2D/Box2D.h>

#include "GameDefines.h"
#include "GenericView.h"
#include "GenericEnemy.h"
#include "Player.h"
#include "ContactListener.h"

using namespace std;

class Game {
	Game() {};
	Game(int width, int height);
	Game(Game const&);
//	Game& operator=(Game const&){};	//wtf copy constructor
	static Game* m_pInstance;
	
	vector<shared_ptr<GenericEnemy> > enemies_;
	
	int scaleW_, scaleH_, scaleX_, scaleY_;
	
	int screenWidth_;
	int screenHeight_;
	
	shared_ptr<GenericView> bounds_;
	shared_ptr<Player> player_;

    mutex enemyMutex_;
	
	b2World* world_;
//	ContactListener* contactListener_;
	
public:
    bool isGameRunning;
	static Game* instance();
	~Game();
	
	void createWorld();
	void update();
	void drawScreen();
	void handleInput(ALLEGRO_KEYBOARD_EVENT event);
	
	shared_ptr<GenericView> getBounds();
	
	b2World* getWorld();
};

#endif /* defined(__ButtGame__Game__) */
