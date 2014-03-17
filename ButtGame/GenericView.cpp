//
//  GenericView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericView.h"

GenericView::GenericView() {
	parentView_ = NULL;
}

GenericView::GenericView(ALLEGRO_DISPLAY* parentView) {
	parentView_ = parentView;
}

void GenericView::draw() {
	cout << "GenericView::draw" << endl;
}