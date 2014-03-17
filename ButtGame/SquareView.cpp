//
//  SquareView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "SquareView.h"
#include <allegro5/allegro_primitives.h>

SquareView::SquareView(int x, int y, int width, int height, GenericView* parentView) {
	parentView_ = parentView;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}

void SquareView::draw() {
//	cout << "SquareView::draw" << endl;
	int x = x_;
	int y = y_;
	if(parentView_) parentView_->mapCoordinatesToParentView(x, y);
	
	al_draw_filled_rectangle(x, y, x + width_, y + height_,  al_map_rgb(255, 255, 255));
}