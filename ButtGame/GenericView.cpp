//
//  GenericView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericView.h"
#include <allegro5/allegro_primitives.h>

#include "Debug.h"

GenericView::GenericView() {
	parentView_ = nullptr;
	backgroundColor_ = al_map_rgb(255, 0, 0);
	
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;
}

GenericView::~GenericView() {
    DBMSG("GenericView::~GenericView");
}

GenericView::GenericView(shared_ptr<GenericView> parentView) {
	parentView_ = parentView;
	backgroundColor_ = al_map_rgb(255, 0, 0);
	
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;
}

GenericView::GenericView(int x, int y, int width, int height, shared_ptr<GenericView> parentView) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	parentView_ = parentView;
	
	backgroundColor_ = al_map_rgb(255, 0, 0);
}

void GenericView::draw() {
	int x = x_;
	int y = y_;
	if(parentView_) parentView_->mapCoordinatesToParentView(x, y);
	
	al_draw_rectangle(x_, y_, x_ + width_, y_ + height_, backgroundColor_, 1);
}

void GenericView::mapCoordinatesToParentView(int& x, int& y) {
	x += x_;
	y += y_;
}

void GenericView::setBackgroundColor(ALLEGRO_COLOR color) {
	backgroundColor_ = color;
}
