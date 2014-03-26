//
//  SquidEnemy.cpp
//  ButtGame
//
//  Created by tim on 3/26/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SquidEnemy.h"
#include "Game.h"

SquidEnemy::SquidEnemy(int x, int y, shared_ptr<GenericView> parentView, int numSpokes) {
	parentView_ = parentView;
	
    isAlive_ = true;
	
	view_ = shared_ptr<SquareView>(new SquareView(x, y, kDefaultEnemySize / 2.f, kDefaultEnemySize / 2.f, true));
	view_->setBackgroundColor(al_map_rgb(255, 255, 0));
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

SquidEnemy::~SquidEnemy() {
	
}


void SquidEnemy::createSpokes() {
	float anglePerSpoke = (M_PI * 2) / numSpokes_;
	
	for(int i = 0; i < numSpokes_; i++) {
		shared_ptr<SquareView> spoke = shared_ptr<SquareView> (new SquareView(0, 0, 90, 5, true));
		spoke->setBackgroundColor(al_map_rgb(255,0,0));
		view_->addSubview(spoke, view_);
		spoke->setBodyDefinition();
		
		//define joint
		b2RevoluteJointDef jointDef;
		jointDef.bodyA = view_->getBody();
		jointDef.bodyB = spoke->getBody();
		
		//set where on the spoke we pin it to the master
//		jointDef.localAnchorA = b2Vec2(kMetersFromPixels((view_->width_ / 2.f)), 0);
//		jointDef.localAnchorB = b2Vec2(kMetersFromPixels((spoke->width_ / 2.f)), 0);
		jointDef.localAnchorB = b2Vec2(kMetersFromPixels((spoke->width_ / 2.f + (view_->width_ * 2.f))), 0);
		
		//space out the joints evenly around a full circle
		jointDef.referenceAngle = anglePerSpoke*i;
		
		//don't collide with it's parent
		jointDef.collideConnected = false;
		
		//Set collision masking so spokes don't colide with other spokes
		
		Game::instance()->getWorld()->CreateJoint(&jointDef);
		
		//start it at it's correct angle transform
		spoke->getBody()->SetTransform(spoke->getBody()->GetPosition(), anglePerSpoke * i);
	}
}

void SquidEnemy::update() {
	GenericEnemy::update();
}