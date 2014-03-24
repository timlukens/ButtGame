//
//  SquareView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SquareView.h"
#include <allegro5/allegro_primitives.h>

#include "Debug.h"
#include "Game.h"

SquareView::SquareView(int x, int y, int width, int height, bool isDynamic) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	
	clipsToBounds_ = false;
	activeView_ = true;
	isDynamic_ = isDynamic;
	
	body_ = nullptr;
	
	this->setBodyDefinition();
}

SquareView::~SquareView() {
    DBMSG("SquareView::~SquareView");
}

//!!!!!!!!!!!!!
//TODO
//!!!!!!!!!!!!!
//Have to translate x_ and y_ back to it's relative position to the superview AFTER we grab the position from the world_
//Box2D now handles the actual position of the object on the screen, but not it's relative position. We need to keep track
//of that ourselves.
void SquareView::drawInView(GenericView* aView) {
	//local variables for real world position as given by the body_
	int x(0), y(0);
	
	if(body_) {
		b2Vec2 position = body_->GetPosition();
		x = kPixelsFromMeters(position.x) - (width_ / 2.f);
		y = kPixelsFromMeters(position.y) - (height_ / 2.f);
	}
		
	//draw this
	al_draw_filled_rectangle(x, y, x+width_, y+height_, backgroundColor_);
		
	this->drawSubViews();
}

void SquareView::setBodyDefinition() {
	//define the body and add to world
	b2BodyDef bodyDef;
	bodyDef.linearDamping = kDefaultLinearDampening;
	
	//we have to define the position in meters, but also in screen coords, so we want to translate from the superview
	int shiftedX = x_;
	int shiftedY = y_;
	this->translateCoordsToScreen(shiftedX, shiftedY);
	
//	bodyDef.position.Set(kMetersFromPixels(shiftedX) + kMetersFromPixels(width_) / 2.f, kMetersFromPixels(shiftedY) + kMetersFromPixels(height_) / 2.f);
	bodyDef.position.Set(kMetersFromPixels(shiftedX), kMetersFromPixels(shiftedY));
	if(isDynamic_) bodyDef.type = b2_dynamicBody;
	
	if(body_) Game::instance()->getWorld()->DestroyBody(body_);
	body_ = Game::instance()->getWorld()->CreateBody(&bodyDef);
	
	//define shape
	b2PolygonShape boxShape;
	boxShape.SetAsBox(kMetersFromPixels(width_) / 2.f, kMetersFromPixels(height_) / 2.f, b2Vec2(0,0), 0);
	
	//fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	
	body_->CreateFixture(&fixtureDef);
}
