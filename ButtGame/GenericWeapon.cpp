//
//  GenericWeapon.cpp
//  ButtGame
//
//  Created by tim on 3/18/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericWeapon.h"

GenericWeapon::GenericWeapon(GenericView* parentView) {
	
}

void GenericWeapon::tick() {
	
}

void GenericWeapon::draw() {
	vector<unique_ptr<GenericProjectile> >::iterator projectile = projectiles_.begin();
	while(projectile != projectiles_.end()) {
        projectileMutex_.lock();
		if(*projectile) {
			(*projectile)->draw();
			++projectile;
		}
        projectileMutex_.unlock();
    }
}

void GenericWeapon::startShooting() {
	isShooting_ = true;
}

void GenericWeapon::stopShooting() {
	isShooting_ = false;
}

void GenericWeapon::setIsDeadlyToEnemies(bool isDeadly) {
	isDeadlyToEnemies_ = isDeadly;
}

bool GenericWeapon::getIsDeadlyToEnemies() {
	return isDeadlyToEnemies_;
}
