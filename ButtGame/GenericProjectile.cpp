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
	
	view_ = new SquareView(parentWeapon_->getParentView()->x_, parentWeapon_->getParentView()->y_, kGenericProjectileSize, kGenericProjectileSize);
	view_->setBackgroundColor(al_map_rgb(255, 255, 0));
	view_->setClipsToBounds(false);
	
	Game* game = Game::instance();
	game->getBounds()->addSubview(shared_ptr<GenericView>(view_), game->getBounds());
}

void GenericProjectile::update() {
	view_->x_ += xVelocity_;
	view_->y_ += yVelocity_;
	
	//check if we're out of bounds
	shared_ptr<GenericView> bounds = Game::instance()->getBounds();
	if(!view_->isInView(bounds)) {
		isAlive_ = false;
		view_->destroyView();
	}
}

SquareView* GenericProjectile::getView() {
	return view_;
}

bool GenericProjectile::getIsAlive() {
	return isAlive_;
}
