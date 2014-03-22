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
	
	shared_ptr<GenericView> pView = parentWeapon_->getParentView();
	
	view_ = shared_ptr<SquareView> (new SquareView(pView->x_ + (pView->width_ / 2) - (kGenericProjectileSize / 2),
												   pView->y_ + (pView->height_ / 2) - (kGenericProjectileSize / 2),
												   kGenericProjectileSize, kGenericProjectileSize));
	view_->setBackgroundColor(al_map_rgb(255, 255, 0));
	view_->setClipsToBounds(false);
	
	Game* game = Game::instance();
	game->getBounds()->addSubview(view_, game->getBounds());
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

shared_ptr<SquareView> GenericProjectile::getView() {
	return view_;
}

bool GenericProjectile::getIsAlive() {
	return isAlive_;
}
