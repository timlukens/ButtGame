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
	bodyDef.linearDamping = kPlayerLinearDamping;
	bodyDef.position.Set((float)x / kMetersToPixels, (float)y / kMetersToPixels);
	if(isDynamic) bodyDef.type = b2_dynamicBody;
	body_ = Game::instance()->getWorld()->CreateBody(&bodyDef);
	
	//define shape
//	b2EdgeShape boxShape;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(width_ / kMetersToPixels / 2, height_ / kMetersToPixels / 2);
	
	//fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	
//	fixtureDef.density = 10.f;
//	fixtureDef.friction = 0.3f;
//	fixtureDef.restitution = 0.f;
	
	body_->CreateFixture(&fixtureDef);
	
//	float x1 = (float)x / kMetersToPixels;
//	float y1 = (float)y / kMetersToPixels;
//	float x2 = ((float)(x + width)) / kMetersToPixels;
//	float y2 = ((float)(y + height)) / kMetersToPixels;
//	
//	boxShape.Set(b2Vec2(x1,y1), b2Vec2(x1,y2));
//	body_->CreateFixture(&fixtureDef);
//	
//	boxShape.Set(b2Vec2(x1,y2), b2Vec2(x2,y2));
//	body_->CreateFixture(&fixtureDef);
//	
//	boxShape.Set(b2Vec2(x2,y2), b2Vec2(x2,y1));
//	body_->CreateFixture(&fixtureDef);
//	
//	boxShape.Set(b2Vec2(x2,y1), b2Vec2(x1,y1));
//	body_->CreateFixture(&fixtureDef);
//	
//	cout << "SquareView: " << x1 << "," << y1 << " - " << x2 << "," << y2 << endl;
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
		
//		std::cout << x << ", " << y << endl;
		
		x_ = x;
		y_ = y;
	}
	
	this->translateCoordsToScreen(x, y);
	
	//draw this
	x -= width_/2;
	y -= height_/2;
	al_draw_filled_rectangle(x, y, x+width_, y+height_, backgroundColor_);
	
	this->drawSubViews();
}

