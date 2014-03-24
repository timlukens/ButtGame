//
//  SpokesEnemy.cpp
//  ButtGame
//
//  Created by tim on 3/24/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SpokesEnemy.h"
#include "Debug.h"
#include "Game.h"
#include "GameDefines.h"
#include <math.h>

SpokesEnemy::SpokesEnemy(int x, int y, shared_ptr<GenericView> parentView, int numSpokes) {
	parentView_ = parentView;
	
    isAlive_ = true;
	
	view_ = shared_ptr<SquareView>(new SquareView(x, y, kDefaultEnemySize, kDefaultEnemySize, true));
	view_->setBackgroundColor(al_map_rgb(255, 0, 0));
	parentView->addSubview(view_, parentView);
	
	movingDirection_ = (kMoveDirection)(rand() % (int)kMoveDirectionCount);
	
    changeDirectionTimer_ = al_create_timer(kChangeDirectionTime);
	changeDirectionQueue_ = al_create_event_queue();
	al_register_event_source(changeDirectionQueue_, al_get_timer_event_source(changeDirectionTimer_));
	al_start_timer(changeDirectionTimer_);
	
	torque_ = 0;
	numSpokes_ = numSpokes;
	
	this->createSpokes();
}

SpokesEnemy::~SpokesEnemy() {
	DBMSG("SpokesEnemy::~SpokesEnemy");
    if(changeDirectionQueue_) { al_destroy_event_queue(changeDirectionQueue_); changeDirectionQueue_ = nullptr; }
    if(changeDirectionTimer_) { al_destroy_timer(changeDirectionTimer_); changeDirectionTimer_ = nullptr; }
}

void SpokesEnemy::createSpokes() {
	float anglePerSpoke = (M_PI * 2) / numSpokes_;
	
	for(int i = 0; i < numSpokes_; i++) {
		shared_ptr<SquareView> spoke = shared_ptr<SquareView> (new SquareView(0, 0, 90, 10, true));
		view_->addSubview(spoke, view_);
		spoke->setBodyDefinition();
		
		b2WeldJointDef jointDef;
		jointDef.bodyA = view_->getBody();
		jointDef.bodyB = spoke->getBody();
		jointDef.localAnchorB = b2Vec2(kMetersFromPixels((spoke->width_ / 2 + (view_->width_ / 2.f))), 0);
		jointDef.referenceAngle = anglePerSpoke*i;
		jointDef.collideConnected = false;
		Game::instance()->getWorld()->CreateJoint(&jointDef);
		
		spoke->getBody()->SetTransform(spoke->getBody()->GetPosition(), anglePerSpoke * i);
	}
}

void SpokesEnemy::update() {
//	view_->getBody()->SetAngularVelocity(20);
	view_->getBody()->ApplyAngularImpulse(.03, true);
	GenericEnemy::update();
}