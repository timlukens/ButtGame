//
//  GenericEnemy.cpp
//  ButtGame
//
//  Created by tim on 3/18/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericEnemy.h"


GenericEnemy::GenericEnemy(int x, int y, shared_ptr<GenericView> parentView) {
	parentView_ = parentView;

    isAlive_ = true;    

	view_ = unique_ptr<SquareView>(new SquareView(x, y, kDefaultEnemySize, kDefaultEnemySize, parentView));
	view_->setBackgroundColor(al_map_rgb(255, 0, 0));
	
	movingDirection_ = (kMoveDirection)(rand() % (int)kMoveDirectionCount);
	
    changeDirectionTimer_ = al_create_timer(kChangeDirectionTime);
	changeDirectionQueue_ = al_create_event_queue();
	al_register_event_source(changeDirectionQueue_, al_get_timer_event_source(changeDirectionTimer_));
	al_start_timer(changeDirectionTimer_);
}

GenericEnemy::~GenericEnemy() {
    cout << "GenericEnemy::~GenericEnemy" << endl;
    if(changeDirectionQueue_) al_destroy_event_queue(changeDirectionQueue_);
    if(timer) al_destroy_timer(timer);
}

SquareView* GenericEnemy::get_view() {
    return &*view_;
}

bool GenericEnemy::is_alive() {
    return isAlive_;
}

void GenericEnemy::make_dead() {
    isAlive_ = false;
}

void GenericEnemy::update() {
	int xVelocity = 0;
	int yVelocity = 0;
	
	ALLEGRO_EVENT e;
	al_get_next_event(changeDirectionQueue_, &e);
	if(e.type == ALLEGRO_EVENT_TIMER)
		movingDirection_ = (kMoveDirection)(rand() % (int)kMoveDirectionCount);
	
	switch(movingDirection_) {
		case kMoveDirectionUp:
			yVelocity = -kDefaultYSpeed;
			break;
			
		case kMoveDirectionDown:
			yVelocity = kDefaultYSpeed;
			break;
			
		case kMoveDirectionLeft:
			xVelocity = -kDefaultXSpeed;
			break;
			
		case kMoveDirectionRight:
			xVelocity = kDefaultXSpeed;
			break;
			
		case kMoveDirectionUpLeft:
			xVelocity = -kDefaultXSpeed;
			yVelocity = -kDefaultYSpeed;
			break;
			
		case kMoveDirectionUpRight:
			xVelocity = kDefaultXSpeed;
			yVelocity = -kDefaultYSpeed;
			break;
			
		case kMoveDirectionDownLeft:
			xVelocity = -kDefaultXSpeed;
			yVelocity = kDefaultYSpeed;
			break;
			
		case kMoveDirectionDownRight:
			xVelocity = kDefaultXSpeed;
			yVelocity = kDefaultYSpeed;
			break;
			
		case kMoveDirectionCount:
			cout << "GenericEnemy: got kMoveDirectionCount. This shouldn't happen. FLIP TABLES!" << endl;
			break;
			
		default:
			break;
	}
	
	//find the actual x,y coordinates inside the parentView
	int x = view_->x_;
	int y = view_->y_;
	parentView_->mapCoordinatesToParentView(x, y);
	
	//make sure we're still in bounds
	if(x + xVelocity > parentView_->x_ && x + view_->width_ + xVelocity < parentView_->x_ + parentView_->width_)
		view_->x_ += xVelocity;
	
	if(y + yVelocity > parentView_->y_ && y + view_->height_ + yVelocity < parentView_->y_ + parentView_->height_)
		view_->y_ += yVelocity;
}

void GenericEnemy::draw() {
	view_->draw();
}
