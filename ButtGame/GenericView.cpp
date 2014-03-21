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
	backgroundColor_ = al_map_rgb(255, 0, 0);
	
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;
}

GenericView::~GenericView() {
    DBMSG("GenericView::~GenericView");
}

GenericView::GenericView(int x, int y, int width, int height) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	
	backgroundColor_ = al_map_rgb(255, 0, 0);
}

void GenericView::drawInView(GenericView* aView) {
	int x = x_;
	int y = y_;
	
	//translate to coordinate system of the view we're drawing in
	if(aView) {
		x += aView->x_;
		y += aView->y_;
	}
	
	//draw this
	al_draw_rectangle(x, y, x+width_, y+height_, backgroundColor_, 1);
	
	
	//draw subViews
	if(subViews_.size()) {
		vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
		while(subView != subViews_.end()) {
			if(*subView) (*subView)->drawInView(this);
		}
	}
}

//void GenericView::draw() {
//	al_draw_rectangle(x_, y_, x_ + width_, y_ + height_, backgroundColor_, 1);
//	
//	vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
//	
//    while(subView != subViews_.end()) {
//        (*subView)->drawInView(shared_ptr<GenericView>(this));
//		subView++;
//	}
//}

void GenericView::addSubview(shared_ptr<GenericView> aView) {
	subViews_.push_back(aView);
}

void GenericView::setBackgroundColor(ALLEGRO_COLOR color) {
	backgroundColor_ = color;
}
