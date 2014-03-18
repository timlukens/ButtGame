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

#define kChangeDirectionTime .6f
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
	SquareView* view_;
	GenericView* parentView_;
	
	ALLEGRO_EVENT_QUEUE* changeDirectionQueue_;
	
	kMoveDirection movingDirection_;
	
public:
	GenericEnemy(int x, int y, GenericView* parentView);
	void update();
	void draw();
};

#endif /* defined(__ButtGame__GenericEnemy__) */
