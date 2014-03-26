//
//  SquidEnemy.h
//  ButtGame
//
//  Created by tim on 3/26/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__SquidEnemy__
#define __ButtGame__SquidEnemy__

#include <iostream>
#include "SpokesEnemy.h"

class SquidEnemy : public SpokesEnemy {
	virtual void createSpokes();
	
public:
	SquidEnemy(int x, int y, shared_ptr<GenericView> parentView, int numSpkes=3);
	~SquidEnemy();
	
	virtual void update();
};

#endif /* defined(__ButtGame__SquidEnemy__) */
