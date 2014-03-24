//
//  SpokesEnemy.h
//  ButtGame
//
//  Created by tim on 3/24/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__SpokesEnemy__
#define __ButtGame__SpokesEnemy__

#include <iostream>
#include "GenericEnemy.h"

class SpokesEnemy : public GenericEnemy {
	
public:
	SpokesEnemy(int x, int y, shared_ptr<GenericView> parentView);
	~SpokesEnemy();
	
    virtual void update();
};

#endif /* defined(__ButtGame__SpokesEnemy__) */
