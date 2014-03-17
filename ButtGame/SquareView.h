//
//  SquareView.h
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__SquareView__
#define __ButtGame__SquareView__

#include <iostream>
#include "GenericView.h"

class SquareView : private GenericView {
	int x_, y_, width_, height_;
	
public:
	SquareView(int x, int y, int width, int height, ALLEGRO_DISPLAY* parentView);
	void draw();
};

#endif /* defined(__ButtGame__SquareView__) */
