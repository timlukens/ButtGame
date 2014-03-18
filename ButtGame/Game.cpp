//
//  Game.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include "Game.h"
#include "SquareView.h"
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <algorithm>

#define GAME_INSET 50

Game::Game(int width, int height) {
	srand(time(NULL));
	screenWidth_ = width;
	screenHeight_ = height;
	
	//achieve resolution independence
	//This way the game is always fullscreen, but the game resolution is always the same
	//no matter what native resolution the OS is on.
	ALLEGRO_MONITOR_INFO mInfo;
	al_get_monitor_info(0, &mInfo);
	int monitorWidth = mInfo.x2 - mInfo.x1;
	int monitorHeight = mInfo.y2 - mInfo.y1;
	
	//calculate stretch amount
	float sx = monitorWidth / (float)screenWidth_;
	float sy = monitorHeight / (float)screenHeight_;
	
	//stretch marks, I mean stretch the screen.
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_scale_transform(&trans, sx, sy);
	al_use_transform(&trans);
	
	//setup bounds. This shit draws a frame
	bounds_ = new GenericView(GAME_INSET, GAME_INSET, width - GAME_INSET * 2, height - GAME_INSET * 2, NULL);
	bounds_->setBackgroundColor(al_map_rgb(255, 255, 255));
	
	//setup dat playa
	player_ = new Player(100,100, bounds_);
	
	//make some god damn enemies
	for(int i = 0; i < 10; i++) {
		
//		GenericEnemy* someButt = new GenericEnemy(200,200, bounds_);
		enemies_.push_back(unique_ptr<GenericEnemy> (new GenericEnemy(rand() % (bounds_->width_ - kDefaultEnemySize), rand() % (bounds_->height_ - kDefaultEnemySize), bounds_)));
	}
}

Game::~Game() {
	//DESTROIDS
}


//graphics tick
void Game::drawScreen() {
	//clear to black
	al_clear_to_color(al_map_rgb(0,0,0));
	
	//draw any generic pushed to this vector
	for(auto &view : views_) {
		view->draw();
	}
	
	//draw any enemies
	for(auto &enemy : enemies_) {
		enemy->draw();
	}
	
	//draw bounds and player
	bounds_->draw();
	player_->draw();
	
	//you know, graphics magic.
	al_flip_display();
}


//game logic tick
void Game::update() {
	player_->update();
	
    SquareView* p_view = player_->get_view();

    vector<unique_ptr<GenericEnemy> >::iterator i = enemies_.begin();    

    while(i != enemies_.end()) {
        GenericEnemy* enemy = (*i).get();
        enemy->update();
        SquareView* e_view = enemy->get_view();
        
        int bottom1 = p_view->y_ + p_view->height_, 
            top1 = p_view->y_, 
            left1 = p_view->x_, 
            right1 = p_view->x_ + p_view->width_;

        int bottom2 = e_view->y_ + e_view->height_,
            top2 = e_view->y_,
            left2 = e_view->x_,
            right2 = e_view->x_ + e_view->width_;

        if( !(bottom1 < top2 || top1 > bottom2 || left1 > right2 || right1 < left2) ) {
            enemy->make_dead();
        }
        if(enemy->is_alive()) {        
            ++i;
        }
        else {
            i = enemies_.erase(i);
        }
	}

}


//I touched my butt
//Eventually interpret if it's a player movement or a UI action (open main menu, whatever)
void Game::handleInput(ALLEGRO_KEYBOARD_EVENT event) {
	player_->handleInput(event);
}
