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

class GenericView {
protected:
	ALLEGRO_DISPLAY* parentView_;
	
public:
	GenericView();
	GenericView(ALLEGRO_DISPLAY* parentView);
	void draw();
};

#endif /* defined(__ButtGame__GenericView__) */
