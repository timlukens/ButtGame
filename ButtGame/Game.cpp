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
}


Game::~Game() {
    DBMSG("Game::~Game");
}

void Game::createWorld() {
	b2Vec2 gravity(0.f, 0.f);
	world_ = new b2World(gravity);
	
//	contactListener_ = new ContactListener();
//	world_->SetContactListener(contactListener_);
	
	bounds_ = shared_ptr<GenericView> (new GenericView(GAME_INSET, GAME_INSET, screenWidth_ - GAME_INSET * 2, (screenHeight_ - GAME_INSET * 2), false));
	player_ = shared_ptr<Player> (new Player(1,1, bounds_));
	
	//make some god damn enemies
	for(int i = 0; i < 10; i++) {
		enemies_.push_back(shared_ptr<GenericEnemy> (new GenericEnemy(rand() % (bounds_->width_ - kDefaultEnemySize), rand() % (bounds_->height_ - kDefaultEnemySize), bounds_)));
//		enemies_.push_back(shared_ptr<GenericEnemy> (new GenericEnemy(bounds_->width_ / 2 - kDefaultEnemySize / 2, bounds_->height_ / 2 - kDefaultEnemySize / 2, bounds_)));
//		enemies_.push_back(shared_ptr<GenericEnemy> (new GenericEnemy(100,100,bounds_)));
	}
}

//graphics tick
void Game::drawScreen() {
	//clear to black
	al_clear_to_color(al_map_rgb(0,0,0));

	//draw bounds
	if(bounds_)
		bounds_->drawInView(nullptr);
	
	//you know, graphics magic.
	al_flip_display();
}


//game logic tick
void Game::update() {
	if(world_) world_->Step(kLogicTick, kVelocityIterations, kPositionIterations);
	if(player_) player_->update();
	
	//enemies
    vector<shared_ptr<GenericEnemy> >::iterator enemy = enemies_.begin();
    while(enemy != enemies_.end()) {
        (*enemy)->update();
		++enemy;
	}
	
	
	
//	//player
//	if(player_) player_->update();
//	
//	
//	//enemies
//    vector<shared_ptr<GenericEnemy> >::iterator enemy = enemies_.begin();
//    while(enemy != enemies_.end()) {
//        (*enemy)->update();
//		
//		//collision detection with player
//		if((*enemy)->getView()->isInView(player_->getHitBox())) player_->setIsAlive(false);
//		
//		//check collision with projectiles
//		vector<shared_ptr<GenericProjectile> >::iterator projectile = player_->getWeapon()->getProjectiles().begin();
//		while(projectile != player_->getWeapon()->getProjectiles().end()) {
//			if(*projectile) {
//				if((*projectile)->getView()->isInView((*enemy)->getView())) {
//					(*enemy)->make_dead();
//					(*projectile)->setIsAlive(false);
//					projectile = player_->getWeapon()->getProjectiles().end();
//				} else {
//					++projectile;
//				}
//			} else {
//				++projectile;
//			}
//		}
//
//		//check if still alive
//        if((*enemy)->is_alive()) ++enemy;
//        else {
//            (*enemy)->getView()->destroyView();
//            enemy = enemies_.erase(enemy);
//        }
//	}
//	
//	if(player_ && !player_->getIsAlive()) isGameRunning = false;
}


//I touched my butt
//Eventually interpret if it's a player movement or a UI action (open main menu, whatever)
void Game::handleInput(ALLEGRO_KEYBOARD_EVENT event) {
	player_->handleInput(event);
}

shared_ptr<GenericView> Game::getBounds() {
	return bounds_;
}

b2World* Game::getWorld() {
	return world_;
}
