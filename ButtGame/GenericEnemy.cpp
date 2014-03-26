//
//  GenericEnemy.cpp
//  ButtGame
//
//  Created by tim on 3/18/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericEnemy.h"
#include "Debug.h"
#include "Game.h"

GenericEnemy::GenericEnemy(int x, int y, shared_ptr<GenericView> parentView) {
	parentView_ = parentView;

    isAlive_ = true;    

	view_ = shared_ptr<SquareView>(new SquareView(x, y, kDefaultEnemySize, kDefaultEnemySize, true));
	view_->setBackgroundColor(al_map_rgb(255, 100, 100));
	parentView->addSubview(view_, parentView);
	
	shared_ptr<SquareView> innerView = shared_ptr<SquareView>(new SquareView(x + kDefaultEnemySize / 4.f, y + kDefaultEnemySize / 4.f,
																			 kDefaultEnemySize / 2.f, kDefaultEnemySize / 2.f, true));
	innerView->setIsAnchord(true);
	view_->addSubview(innerView, view_);
	
	movingDirection_ = (kMoveDirection)(rand() % (int)kMoveDirectionCount);
	
    changeDirectionTimer_ = al_create_timer(kChangeDirectionTime);
	changeDirectionQueue_ = al_create_event_queue();
	al_register_event_source(changeDirectionQueue_, al_get_timer_event_source(changeDirectionTimer_));
	al_start_timer(changeDirectionTimer_);
}

GenericEnemy::~GenericEnemy() {
    DBMSG("GenericEnemy::~GenericEnemy");
    if(changeDirectionQueue_) { al_destroy_event_queue(changeDirectionQueue_); changeDirectionQueue_ = nullptr; }
    if(changeDirectionTimer_) { al_destroy_timer(changeDirectionTimer_); changeDirectionTimer_ = nullptr; }
}

shared_ptr<SquareView> GenericEnemy::getView() {
	return view_;
}

int GenericEnemy::get_x() {
    return view_->x_;
}

int GenericEnemy::get_y() {
    return view_->y_;
}

int GenericEnemy::get_width() {
    return view_->width_;
}

int GenericEnemy::get_height() {
    return view_->height_;
}

bool GenericEnemy::is_alive() {
    return isAlive_;
}

void GenericEnemy::make_dead() {
    isAlive_ = false;
}

void GenericEnemy::update() {
	xVelocity_ = 0;
	yVelocity_ = 0;
	
	ALLEGRO_EVENT e;
	if(al_get_next_event(changeDirectionQueue_, &e)) {
	    if(e.type == ALLEGRO_EVENT_TIMER) {
		    movingDirection_ = (kMoveDirection)(rand() % (int)kMoveDirectionCount);
        }
    }

	switch(movingDirection_) {
		case kMoveDirectionUp:
			yVelocity_ = -kDefaultYSpeed;
			break;
			
		case kMoveDirectionDown:
			yVelocity_ = kDefaultYSpeed;
			break;
			
		case kMoveDirectionLeft:
			xVelocity_ = -kDefaultXSpeed;
			break;
			
		case kMoveDirectionRight:
			xVelocity_ = kDefaultXSpeed;
			break;
			
		case kMoveDirectionUpLeft:
			xVelocity_ = -kDefaultXSpeed;
			yVelocity_ = -kDefaultYSpeed;
			break;
			
		case kMoveDirectionUpRight:
			xVelocity_ = kDefaultXSpeed;
			yVelocity_ = -kDefaultYSpeed;
			break;
			
		case kMoveDirectionDownLeft:
			xVelocity_ = -kDefaultXSpeed;
			yVelocity_ = kDefaultYSpeed;
			break;
			
		case kMoveDirectionDownRight:
			xVelocity_ = kDefaultXSpeed;
			yVelocity_ = kDefaultYSpeed;
			break;
			
		case kMoveDirectionCount:
			cout << "GenericEnemy: got kMoveDirectionCount. This shouldn't happen. FLIP TABLES!" << endl;
			break;
			
		default:
			break;
	}
	
	view_->getBody()->ApplyForceToCenter(b2Vec2(xVelocity_, yVelocity_), true);
}
