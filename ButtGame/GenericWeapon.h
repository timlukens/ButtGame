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
#include <allegro5/allegro.h>
#include "GenericView.h"

class GenericWeapon {
	GenericView* parentView_;
	ALLEGRO_TIMER* shootTimer_;
	bool isShooting_;
	
public:
	GenericWeapon(GenericView* parentView);
	
	void tick();
	void draw();
	void startShooting();
	void stopShooting();
};

#endif /* defined(__ButtGame__GenericWeapon__) */
