//
//  GenericWeapon.cpp
//  ButtGame
//
//  Created by tim on 3/18/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericWeapon.h"

GenericWeapon::GenericWeapon(shared_ptr<GenericView> parentView) {
	parentView_ = parentView;
	
	fireRate_ = kGenericWeaponFireRate;
	maxBulletsOnScreen_ = kGenericWeaponMaxBullets;
	isDeadlyToEnemies_ = true;
	isShooting_ = false;
	canShoot_ = true;
	
	newBulletXFactor_ = 0;
	newBulletYFactor_ = 0;
	
	shootTimer_ = al_create_timer(fireRate_);
	shootQueue_ = al_create_event_queue();
	al_register_event_source(shootQueue_, al_get_timer_event_source(shootTimer_));
	al_start_timer(shootTimer_);
}

void GenericWeapon::update() {
	if(!newBulletYFactor_ && !newBulletXFactor_) this->stopShooting();
	
	//check for new bullets
	if(isShooting_) {
		ALLEGRO_EVENT e;
		if(al_get_next_event(shootQueue_, &e)) {
			if(e.type == ALLEGRO_EVENT_TIMER && projectiles_.size() < maxBulletsOnScreen_) {
				canShoot_ = true;
				al_flush_event_queue(shootQueue_);
			}
		}
	}
	
	if((newBulletXFactor_ != 0 || newBulletYFactor_ != 0) && canShoot_) {
		canShoot_ = false;
		shared_ptr<GenericProjectile> p = shared_ptr<GenericProjectile>(new GenericProjectile(this, newBulletXFactor_ * kGenericProjectileSpeed,
																							  newBulletYFactor_ * kGenericProjectileSpeed));
		projectiles_.push_back(p);
	}
	
	vector<shared_ptr<GenericProjectile> >::iterator projectile = projectiles_.begin();
	
    while(projectile != projectiles_.end()) {
        (*projectile)->update();
		
        if((*projectile)->getIsAlive()) {
            ++projectile;
        }
        else {
			(*projectile)->getView()->destroyView();
			projectile = projectiles_.erase(projectile);
        }
	}

}

void GenericWeapon::startShooting() {
	isShooting_ = true;
}

void GenericWeapon::setNewBulletXFactor(float xFactor) {
	newBulletXFactor_ = xFactor;
}

void GenericWeapon::setNewBulletYFactor(float yFactor) {
	newBulletYFactor_ = yFactor;
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

shared_ptr<GenericView> GenericWeapon::getParentView() {
	return parentView_;
}

vector<shared_ptr<GenericProjectile>> GenericWeapon::getProjectiles() {
	return projectiles_;
}
