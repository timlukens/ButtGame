//
//  GenericWeapon.h
//  ButtGame
//
//  Created by tim on 3/18/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__GenericWeapon__
#define __ButtGame__GenericWeapon__

#include <iostream>
#include <vector>
#include <thread>
#include <allegro5/allegro.h>
#include "GenericView.h"
#include "GenericProjectile.h"

using namespace std;

class GenericWeapon {
	GenericView* parentView_;
	ALLEGRO_TIMER* shootTimer_;
	
	bool isShooting_;
	bool isDeadlyToEnemies_;
	
	int maxBulletsOnScreen_;
	float fireRate_;
	
	vector<unique_ptr<GenericProjectile>> projectiles_;
	
	mutex projectileMutex_;
	
public:
	GenericWeapon(GenericView* parentView);
	
	void tick();
	void draw();
	
	void startShooting();
	void stopShooting();
	
	void setIsDeadlyToEnemies(bool isDeadly);
	bool getIsDeadlyToEnemies();
};

#endif /* defined(__ButtGame__GenericWeapon__) */
