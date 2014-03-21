//
//  GenericView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericView.h"
#include <allegro5/allegro_primitives.h>

#include "Debug.h"

GenericView::GenericView() {
	backgroundColor_ = al_map_rgb(255, 0, 0);
	
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;

    activeView_ = true;
}

GenericView::~GenericView() {
    DBMSG("GenericView::~GenericView");
}

GenericView::GenericView(int x, int y, int width, int height) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	
	backgroundColor_ = al_map_rgb(255, 0, 0);

    activeView_ = true;
}

void GenericView::drawInView(GenericView* aView) {
	int x = x_;
	int y = y_;
	
	this->translateCoordsToView(x, y, aView);
	
	//draw this
	al_draw_rectangle(x, y, x+width_, y+height_, backgroundColor_, 1);
	
	GenericView::drawSubViews();
}

void GenericView::translateCoordsToView(int& x, int& y, GenericView* aView) {
	//translate to coordinate system of the view we're drawing in
	if(aView) {
		x += aView->x_;
		y += aView->y_;
		
		if(x < aView->x_) x = aView->x_;
		if(x > aView->x_ + aView->width_ - width_) x = aView->x_ + aView->width_ - width_;
		
		if(y < aView->y_) y = aView->y_;
		if(y > aView->y_ + aView->height_ - height_) y = aView->y_ + aView->height_ - height_;
	}
}

void GenericView::drawSubViews() {
    //draw subViews
    vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
    while(subView != subViews_.end()) {
        if(*subView) {
            if((*subView)->isActive()) {
                (*subView)->drawInView(this);
                ++subView;
            }
            else {
                subView = subViews_.erase(subView);
            }
        }
        else {
            subView = subViews_.erase(subView);
        }

    }
}

void GenericView::addSubview(shared_ptr<GenericView> aView, shared_ptr<GenericView> pView) {
    subViews_.push_back(aView);
    aView->setSuperView(pView);
}

void GenericView::setSuperView(shared_ptr<GenericView> aView) {
    superView_ = aView;
}

shared_ptr<GenericView> GenericView::getSuperView() {
    return superView_;
}

void GenericView::removeFromSuperView() {
    if(superView_) {
        return superView_->removeView(this);
    }
}

void GenericView::removeView(GenericView* aView) {
    vector<shared_ptr<GenericView> >::iterator subView = subViews_.begin();
    while(subView != subViews_.end()) {
        if((*subView)) {
            if((*subView).get() == aView) {
                subView = subViews_.erase(subView);
            }
            ++subView;
        }
        else {
            subView = subViews_.erase(subView);
        }
    }
}

void GenericView::setBackgroundColor(ALLEGRO_COLOR color) {
	backgroundColor_ = color;
}

void GenericView::destroyView() {
    activeView_ = false;    
}

bool GenericView::isActive() {
    return activeView_;
}
