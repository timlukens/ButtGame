//
//  GenericEnemy.h
//  ButtGame
//
//  Created by tim on 3/18/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__GenericEnemy__
#define __ButtGame__GenericEnemy__

#include <iostream>
#include "SquareView.h"
#include "GameDefines.h"
#include "SineGenerator.h"
#include "SquareGenerator.h"

#define kChangeDirectionTime 0.6f
#define kDefaultEnemySize 25

enum kMoveDirection {
	kMoveDirectionUp = 0,
	kMoveDirectionDown,
	kMoveDirectionLeft,
	kMoveDirectionRight,
	kMoveDirectionUpLeft,
	kMoveDirectionUpRight,
	kMoveDirectionDownLeft,
	kMoveDirectionDownRight,
	kMoveDirectionCount
};

class GenericEnemy {
protected:
	shared_ptr<SquareView> view_;
	shared_ptr<GenericView> parentView_;
	
	ALLEGRO_EVENT_QUEUE* changeDirectionQueue_;
    ALLEGRO_TIMER* changeDirectionTimer_;

	kMoveDirection movingDirection_;
    bool isAlive_;
	
	float xVelocity_, yVelocity_;
	
	shared_ptr<SineGenerator> sine1_;
	shared_ptr<SineGenerator> sine2_;
	shared_ptr<SineGenerator> sine3_;
	shared_ptr<SquareGenerator> square1_;
	shared_ptr<SquareGenerator> square2_;
	shared_ptr<SquareGenerator> square3_;

public:
	GenericEnemy() {}
	GenericEnemy(int x, int y, shared_ptr<GenericView> parentView);
	~GenericEnemy();
	
	shared_ptr<SquareView> getView();
	int get_x();
	int get_y();
	int get_width();
	int get_height();
	
	bool is_alive();
	void make_dead();
	
    virtual void update();
};

#endif /* defined(__ButtGame__GenericEnemy__) */
