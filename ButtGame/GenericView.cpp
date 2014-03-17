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
	cout << "GenericView::draw" << endl;
}