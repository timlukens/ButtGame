//
//  GenericView.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "GenericView.h"
#include "Game.h"
#include <allegro5/allegro_primitives.h>

#include "Debug.h"

GenericView::GenericView() {
	backgroundColor_ = al_map_rgb(255, 0, 0);
	
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;

    activeView_ = true;
	clipsToBounds_ = true;
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
	clipsToBounds_ = true;
}

void GenericView::drawInView(GenericView* aView) {
	int x = x_;
	int y = y_;
	
//	this->translateCoordsToView(x, y, aView);
	this->translateCoordsToScreen(x, y);
	
	//draw this
	al_draw_rectangle(x, y, x+width_, y+height_, backgroundColor_, 1);
	
	this->drawSubViews();
}

void GenericView::translateCoordsToView(int& x, int& y, GenericView* aView) {
	GenericView* view = this->superView_.get();
	GenericView* lastView = nullptr;
	
	while(view && aView != lastView) {
		//translate to coordinate system of the view we're drawing in
		if(aView) {
			x += view->x_;
			y += view->y_;
			
			//check bounds of view we're translating into
			//but only if we clip to bounds
			if(clipsToBounds_ && view == superView_.get()) {
				if(x < view->x_) {
					x = view->x_;
					if(view != this) x_ = x - view->x_;
				}
				if(x + width_ > view->x_ + view->width_) {
					x = view->x_ + view->width_ - width_;
					if(view != this) x_ = x - view->x_;
				}
				
				if(y < view->y_){
					y = view->y_;
					if(view != this) y_ = y - view->y_;
				}
				if(y + height_ > view->y_ + view->height_) {
					y = view->y_ + view->height_ - height_;
					if(view != this) y_ = y - view->y_;
				}
			}
		}
		lastView = view;
		view = view->getSuperView().get();
	}
}

void GenericView::translateCoordsToScreen(int&x, int& y) {
	GenericView* view = superView_.get();
	
	while(view) {
		//translate to coordinate system of the view we're drawing in
		if(view) {
			x += view->x_;
			y += view->y_;
			
			//check bounds of view we're translating into
			//but only if we clip to bounds
			if(clipsToBounds_ && view == superView_.get()) {
				if(x < view->x_) {
					x = view->x_;
					if(view != this) x_ = x - view->x_;
				}
				if(x + width_ > view->x_ + view->width_) {
					x = view->x_ + view->width_ - width_;
					if(view != this) x_ = x - view->x_;
				}
				
				if(y < view->y_){
					y = view->y_;
					if(view != this) y_ = y - view->y_;
				}
				if(y + height_ > view->y_ + view->height_) {
					y = view->y_ + view->height_ - height_;
					if(view != this) y_ = y - view->y_;
				}
			}
		}
		view = view->getSuperView().get();
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

bool GenericView::isInView(shared_ptr<GenericView> aView) {
//	Game* game = Game::instance();
	
	int x = x_, y = y_;
	int otherX = aView->x_, otherY = aView->y_;
	
	this->translateCoordsToScreen(x, y);
	aView->translateCoordsToScreen(otherX, otherY);
	
//	this->translateCoordsToView(x, y, game->getBounds().get());
//	aView->translateCoordsToView(otherX, otherY, game->getBounds().get());
	
	if(y + height_ < otherY || y > otherY + aView->height_ || x > otherX + aView->width_ || x + width_ < otherX) return false;
	return true;
}

void GenericView::setClipsToBounds(bool clips) {
	clipsToBounds_ = clips;
}
