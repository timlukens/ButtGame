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
#include <mutex>
#include <allegro5/allegro.h>
#include "GenericView.h"
#include "GenericProjectile.h"

#define kGenericWeaponFireRate 2;
#define kGenericWeaponMaxBullets 4;

using namespace std;

class GenericWeapon {
	GenericView* parentView_;
	
	ALLEGRO_TIMER* shootTimer_;
	ALLEGRO_EVENT_QUEUE* shootQueue_;
	
	bool isShooting_;
	bool isDeadlyToEnemies_;
	
	int maxBulletsOnScreen_;
	float fireRate_;
	
	vector<unique_ptr<GenericProjectile>> projectiles_;
	
	mutex projectileMutex_;
	
public:
	GenericWeapon(GenericView* parentView);
	
	void update();
	void draw();
	
	GenericView* getParentView();
	
	void startShooting();
	void stopShooting();
	
	void setIsDeadlyToEnemies(bool isDeadly);
	bool getIsDeadlyToEnemies();
};

#endif /* defined(__ButtGame__GenericWeapon__) */
