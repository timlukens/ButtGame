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

#define kMaxTorque 1000
#define kTorqueStep 1

class SpokesEnemy : public GenericEnemy {
	void createSpokes();
	
	int torque_;
	int numSpokes_;
	
public:
	SpokesEnemy(int x, int y, shared_ptr<GenericView> parentView, int numSpokes=2);
	~SpokesEnemy();
	
    virtual void update();
};

#endif /* defined(__ButtGame__SpokesEnemy__) */
