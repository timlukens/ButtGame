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
#include <vector>
#include <allegro5/allegro.h>

using namespace std;

class GenericView {
protected:
	ALLEGRO_COLOR backgroundColor_;
	vector<shared_ptr<GenericView>> subViews_;
	
public:
	GenericView();
	~GenericView();
	GenericView(int x, int y, int width, int height);
	
//	virtual void draw();
	virtual void drawInView(shared_ptr<GenericView> aView);
	void addSubview(shared_ptr<GenericView> aView);
	void setBackgroundColor(ALLEGRO_COLOR color);
	
	int x_, y_, width_, height_;
};

#endif /* defined(__ButtGame__GenericView__) */
