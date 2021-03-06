//
//  GenericProjectile.h
//  ButtGame
//
//  Created by tim on 3/20/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__GenericProjectile__
#define __ButtGame__GenericProjectile__

#include <iostream>
#include "Debug.h"
#include "SquareView.h"
#include "GameDefines.h"

#define kGenericProjectileSpeed 960.f / LOGIC_FPS
#define kGenericProjectileSize 5

class GenericWeapon;

class GenericProjectile {
	GenericWeapon* parentWeapon_;
	shared_ptr<SquareView> view_;
	
	int xVelocity_, yVelocity_;
	
	bool isAlive_;
	
public:
	GenericProjectile(GenericWeapon* parentWeapon, int xVelocity, int yVelocity);
	~GenericProjectile();
	
	void update();
	
	shared_ptr<SquareView> getView();
	bool getIsAlive();
	void setIsAlive(bool isAlive);
};

#endif /* defined(__ButtGame__GenericProjectile__) */
