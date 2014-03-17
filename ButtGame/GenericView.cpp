//
//  GenericView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericView.h"
#include <allegro5/allegro_primitives.h>

GenericView::GenericView() {
	parentView_ = NULL;
}

GenericView::GenericView(GenericView* parentView) {
	parentView_ = parentView;
}

GenericView::GenericView(int x, int y, int width, int height, GenericView* parentView) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	parentView_ = parentView;
}

void GenericView::draw() {
	int x = x_;
	int y = y_;
	if(parentView_) parentView_->mapCoordinatesToParentView(x, y);
	
	al_draw_rectangle(x_, y_, x_ + width_, y_ + height_, al_map_rgb(255, 0, 0), 1);
}

void GenericView::mapCoordinatesToParentView(int& x, int& y) {
	x += x_;
	y += y_;
}