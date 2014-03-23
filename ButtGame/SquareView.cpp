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
	
	//define the body and add to world
	b2BodyDef bodyDef;
	bodyDef.position.Set((float)x / kMetersToPixels, (float)y / kMetersToPixels);
	if(isDynamic) bodyDef.type = b2_dynamicBody;
	body_ = Game::instance()->getWorld()->CreateBody(&bodyDef);
	
	//define shape
	b2PolygonShape boxShape;
	boxShape.SetAsBox(width_ / kMetersToPixels / 2, height_ / kMetersToPixels / 2);
	
	//fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.f;
	fixtureDef.isSensor = true;
	
	body_->CreateFixture(&fixtureDef);
	
//	//map 0,0 - width,0
//	box.Set(b2Vec2((float)x / kMetersToPixels, (float)y / kMetersToPixels), b2Vec2((float)(x+width) / kMetersToPixels, 0));
//	body_->CreateFixture(&boxDef);
//	
//	//map 0,0 - 0,height
//	box.Set(b2Vec2((float)x / kMetersToPixels, (float)y / kMetersToPixels), b2Vec2(0, (float)(y+height) / kMetersToPixels));
//	body_->CreateFixture(&boxDef);
//	
//	//map 0,height - widht,height
//	box.Set(b2Vec2((float)x / kMetersToPixels, (float)(y+height) / kMetersToPixels), b2Vec2((float)(x+width) / kMetersToPixels, (float)(y+height) / kMetersToPixels));
//	body_->CreateFixture(&boxDef);
//	
//	//map widht,height - widht,0
//	box.Set(b2Vec2((float)(x+width) / kMetersToPixels, (float)(y+height) / kMetersToPixels), b2Vec2((float)(x+width), 0));
//	body_->CreateFixture(&boxDef);
}

SquareView::~SquareView() {
    DBMSG("SquareView::~SquareView");
}

void SquareView::drawInView(GenericView* aView) {
	int x = x_;
	int y = y_;
	
	if(body_) {
		b2Vec2 position = body_->GetPosition();
		x = position.x * kMetersToPixels;
		y = position.y * kMetersToPixels;
		x_ = x;
		y_ = y;
	}
	
//	this->translateCoordsToView(x, y, aView);
	this->translateCoordsToScreen(x, y);
	
	//draw this
	al_draw_filled_rectangle(x, y, x+width_, y+height_, backgroundColor_);
	
	this->drawSubViews();
}

