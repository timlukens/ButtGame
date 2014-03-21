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

SquareView::SquareView(int x, int y, int width, int height) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}

SquareView::~SquareView() {
    DBMSG("SquareView::~SquareView");
}

void SquareView::drawInView(GenericView* aView) {
	int x = x_;
	int y = y_;
	
	//translate to coordinate system of the view we're drawing in
	if(aView) {
		x += aView->x_;
		y += aView->y_;
	}
	
	//draw this
	al_draw_filled_rectangle(x, y, x+width_, y+height_, backgroundColor_);
	
	
	//draw subViews
    vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
    while(subView != subViews_.end()) {    
        if(*subView) (*subView)->drawInView(this);
        ++subView;
    }
}

//void SquareView::draw() {
//	al_draw_filled_rectangle(x_, y_, x_ + width_, y_ + height_,  backgroundColor_);
//	
//	//draw subViews
//	vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
//    while(subView != subViews_.end()) {
//        (*subView)->drawInView(shared_ptr<GenericView>(this));
//		subView++;
//	}
//}
