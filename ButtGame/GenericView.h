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
#include <memory>
#include <allegro5/allegro.h>

using namespace std;

class GenericView {
protected:
	shared_ptr<GenericView> parentView_;
	ALLEGRO_COLOR backgroundColor_;
	
public:
	GenericView();
	~GenericView();
    GenericView(shared_ptr<GenericView> parentView);
	GenericView(int x, int y, int width, int height, shared_ptr<GenericView> parentView);
	
	virtual void draw();
	void mapCoordinatesToParentView(int& x, int& y);
	void setBackgroundColor(ALLEGRO_COLOR color);
	
	int x_, y_, width_, height_;
};

#endif /* defined(__ButtGame__GenericView__) */
