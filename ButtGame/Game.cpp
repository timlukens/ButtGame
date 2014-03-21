//
//  Game.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#include <vector>
#include <algorithm>

#include <allegro5/allegro_primitives.h>

#include "Game.h"
#include "Debug.h"
#include "SquareView.h"

#define GAME_INSET 50


Game* Game::m_pInstance = NULL;

Game* Game::instance() {
	if(!m_pInstance) {
		m_pInstance = new Game(GAME_WIDTH, GAME_HEIGHT);
	}
	
	return m_pInstance;
}


Game::Game(int width, int height) {
	srand(time(NULL));
	screenWidth_ = width;
	screenHeight_ = height;
    isGameRunning = true;
	
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
	bounds_ = shared_ptr<GenericView>(new GenericView(GAME_INSET, GAME_INSET, width - GAME_INSET * 2, height - GAME_INSET * 2));
	bounds_->setBackgroundColor(al_map_rgb(255, 255, 255));
	
	//setup dat playa
	player_ = shared_ptr<Player>(new Player(100,100, bounds_));
	
	//make some god damn enemies
	for(int i = 0; i < 3; i++) {
		
//		GenericEnemy* someButt = new GenericEnemy(200,200, bounds_);
		enemies_.push_back(shared_ptr<GenericEnemy> (new GenericEnemy(rand() % (bounds_->width_ - kDefaultEnemySize), rand() % (bounds_->height_ - kDefaultEnemySize), bounds_)));
	}
}

Game::~Game() {
    DBMSG("Game::~Game");
}

//graphics tick
void Game::drawScreen() {
	//clear to black
	al_clear_to_color(al_map_rgb(0,0,0));
	
	//draw any generic pushed to this vector
//	for(auto &view : views_) {
//		view->draw();
//	}
	
	//draw any enemies
//    vector<shared_ptr<GenericEnemy> >::iterator enemy = enemies_.begin();
//
//    while(enemy != enemies_.end()) {
//        enemyMutex_.lock();
//		if(*enemy) {
//			(*enemy)->draw();
//			++enemy;
//		}
//        enemyMutex_.unlock();
//    }    

	//draw bounds and player
	bounds_->drawInView(nullptr);
//	player_->draw();
	
	//you know, graphics magic.
	al_flip_display();
}


//game logic tick
void Game::update() {
	if(player_) player_->update();
	
    vector<shared_ptr<GenericEnemy> >::iterator enemy = enemies_.begin();

    while(enemy != enemies_.end()) {
        (*enemy)->update();

        int bottom1 = player_->get_y() + player_->get_height(), 
            top1 = player_->get_y(), 
            left1 = player_->get_x(), 
            right1 = player_->get_x() + player_->get_width();

        int bottom2 = (*enemy)->get_y() + (*enemy)->get_height(),
            top2 = (*enemy)->get_y(),
            left2 = (*enemy)->get_x(),
            right2 = (*enemy)->get_x() + (*enemy)->get_width();

        if( !(bottom1 < top2 || top1 > bottom2 || left1 > right2 || right1 < left2) ) {
            (*enemy)->make_dead();
        }

        if((*enemy)->is_alive()) {        
            ++enemy;
        }
        else {
            (*enemy)->getView()->destroyView();
            enemy = enemies_.erase(enemy);
        }
	}

}


//I touched my butt
//Eventually interpret if it's a player movement or a UI action (open main menu, whatever)
void Game::handleInput(ALLEGRO_KEYBOARD_EVENT event) {
	player_->handleInput(event);
}

shared_ptr<GenericView> Game::getBounds() {
	return bounds_;
}
