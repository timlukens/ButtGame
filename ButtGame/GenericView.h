//
//  GenericView.h
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef __ButtGame__GenericView__
#define __ButtGame__GenericView__

#include <iostream>
#include <allegro5/allegro.h>

using namespace std;

class GenericView {
protected:
	GenericView* parentView_;
	
public:
	GenericView();
	GenericView(GenericView* parentView);
	GenericView(int x, int y, int width, int height, GenericView* parentView);
	virtual void draw();
	
	int x_, y_, width_, height_;
};

#endif /* defined(__ButtGame__GenericView__) */
