//
//  GenericProjectile.cpp
//  ButtGame
//
//  Created by tim on 3/20/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericProjectile.h"
#include "GenericWeapon.h"
#include "Game.h"

GenericProjectile::GenericProjectile(GenericWeapon* parentWeapon, int xVelocity, int yVelocity) {
	parentWeapon_ = parentWeapon;
	
	isAlive_ = true;
	
	xVelocity_ = xVelocity;
	yVelocity_ = yVelocity;
	
	view_ = new SquareView(parentWeapon_->getParentView()->x_, parentWeapon_->getParentView()->y_, kGenericProjectileSize, kGenericProjectileSize, shared_ptr<GenericView>(parentWeapon_->getParentView()));
}

void GenericProjectile::draw() {
	view_->draw();
}

void GenericProjectile::update() {
	//find the actual x,y coordinates inside the parentView
	int x = view_->x_;
	int y = view_->y_;
	parentWeapon_->getParentView()->mapCoordinatesToParentView(x, y);
	
	x += xVelocity_;
	y += yVelocity_;
	
	view_->x_ = x;
	view_->y_ = y;
	
	//check if we're out of bounds
	shared_ptr<GenericView> bounds = Game::instance()->getBounds();
	if(x < bounds->x_ || x > bounds->x_ + bounds->width_ || y < bounds->y_ || y > bounds->height_)
		isAlive_ = false;
}

SquareView* GenericProjectile::getView() {
	return view_;
}

bool GenericProjectile::getIsAlive() {
	return isAlive_;
}