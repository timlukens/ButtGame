//
//  main.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

//Start timer
#include <stdio.h>
#include <thread>
#include <allegro5/allegro.h>
#include "Game.h"

static void InputThread(shared_ptr<Game> game);
static void UpdateThread(shared_ptr<Game> game);
//static void InputThread(Game* game);
//static void UpdateThread(Game* game);

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
		
	//Various inits
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return EXIT_FAILURE;
    }
	
	al_install_keyboard();
	
	ALLEGRO_MONITOR_INFO mInfo;
	al_get_monitor_info(0, &mInfo);
	int width = (mInfo.x2 - mInfo.x1) / GAME_SIZE_DIVISOR;
	int height = (mInfo.y2 - mInfo.y1) / GAME_SIZE_DIVISOR;
	
//	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    display = al_create_display(width, height);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return EXIT_FAILURE;
    }
	
	eventQueue = al_create_event_queue();
	if(!eventQueue) {
		fprintf(stderr, "failed to create eventQueue!\n");
		al_destroy_display(display);
		return EXIT_FAILURE;
	}

	shared_ptr<Game> game(Game::instance());
//	Game* game = Game::instance();
    
    thread inputThread(InputThread, game);
	thread updateThread(UpdateThread, game);
	
	inputThread.detach();
    updateThread.detach();
    
    ALLEGRO_TIMER* timer;
    
    timer = al_create_timer(1.0 / LOGIC_FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return EXIT_FAILURE;
	}
    
    //Tie events to queue
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    
    //Start timer
	al_start_timer(timer);

    //Main loop
	while(game->isGameRunning)
	{
		ALLEGRO_EVENT e;
		al_wait_for_event(eventQueue, &e);
		
		if(e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game->isGameRunning = false;
		
		//Update display
		game->drawScreen();
	}
    
	al_destroy_timer(timer);
    //Cleaning
    al_destroy_display(display);
	al_destroy_event_queue(eventQueue);

	
    return EXIT_SUCCESS;
}

static void InputThread(shared_ptr<Game> game) {
//static void InputThread(Game* game) {
	ALLEGRO_EVENT_QUEUE *inputQueue;
		
	inputQueue = al_create_event_queue();
	if(!inputQueue) {
		fprintf(stderr, "failed to create inputQueue!\n");
		exit(1);
	}
	
	al_register_event_source(inputQueue, al_get_keyboard_event_source());
	
	while(game->isGameRunning) {
		ALLEGRO_EVENT e;
		al_wait_for_event(inputQueue, &e);
	    if(e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            game->isGameRunning = false; 
		if(e.type == ALLEGRO_EVENT_KEY_DOWN || ALLEGRO_EVENT_KEY_UP)
			game->handleInput(e.keyboard);
	}
}

static void UpdateThread(shared_ptr<Game> game) {
//static void UpdateThread(Game* game) {
	ALLEGRO_EVENT_QUEUE* updateQueue;
	
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / LOGIC_FPS);
	if(!timer) {
		fprintf(stderr, "failed to create update timer!\n");
		exit(1);
	}
	
	updateQueue = al_create_event_queue();
	if(!updateQueue) {
		fprintf(stderr, "failed to create updateQueue!\n");
		exit(1);
	}
	
	al_register_event_source(updateQueue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	
	while(game->isGameRunning) {
		ALLEGRO_EVENT e;
		al_wait_for_event(updateQueue, &e);
		
		if(e.type == ALLEGRO_EVENT_TIMER)
			game->update();
	}
}
