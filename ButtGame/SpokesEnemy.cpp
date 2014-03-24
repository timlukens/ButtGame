//
//  SpokesEnemy.cpp
//  ButtGame
//
//  Created by tim on 3/24/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SpokesEnemy.h"
#include "Debug.h"

SpokesEnemy::SpokesEnemy(int x, int y, shared_ptr<GenericView> parentView) {
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
}

SpokesEnemy::~SpokesEnemy() {
	DBMSG("SpokesEnemy::~SpokesEnemy");
    if(changeDirectionQueue_) { al_destroy_event_queue(changeDirectionQueue_); changeDirectionQueue_ = nullptr; }
    if(changeDirectionTimer_) { al_destroy_timer(changeDirectionTimer_); changeDirectionTimer_ = nullptr; }
}

void SpokesEnemy::update() {
	GenericEnemy::update();
	
//	view_->getBody()->ApplyAngularImpulse(1, true);
//	cout << view_->getBody()->GetAngle() << endl;
}