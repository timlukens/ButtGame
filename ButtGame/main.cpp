//
//  main.cpp
//  ButtGame
//
//  Created by tim on 3/17/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

//Start timer
#include <stdio.h>
#include <allegro5/allegro.h>
#include "Game.h"

static void* InputThread(ALLEGRO_THREAD* thr, void* arg);
static void* UpdateThread(ALLEGRO_THREAD* thr, void* arg);

int main(int argc, char **argv)
{
	std::cout << "Rockin\n";
	
    ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_THREAD* inputThread;
	ALLEGRO_THREAD* updateThread;
	
	bool isGameRunning = true;
	
	//Various inits
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return EXIT_FAILURE;
    }
	
	al_install_keyboard();
	
	timer = al_create_timer(1.0 / LOGIC_FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return EXIT_FAILURE;
	}
	
	ALLEGRO_MONITOR_INFO mInfo;
	al_get_monitor_info(0, &mInfo);
	int width = mInfo.x2 - mInfo.x1;
	int height = mInfo.y2 - mInfo.y1;
	
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    display = al_create_display(width, height);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
        return EXIT_FAILURE;
    }
	
	eventQueue = al_create_event_queue();
	if(!eventQueue) {
		fprintf(stderr, "failed to create eventQueue!\n");
		al_destroy_timer(timer);
		al_destroy_display(display);
		return EXIT_FAILURE;
	}
	
	
	//Tie events to queue
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	
	//Start timer
	al_start_timer(timer);
	
	Game* game = Game::instance();
	
	inputThread = al_create_thread(InputThread, game);
	al_start_thread(inputThread);
	
	updateThread = al_create_thread(UpdateThread, game);
	al_start_thread(updateThread);
	
	//Main loop
	while(isGameRunning)
	{
		ALLEGRO_EVENT e;
		al_wait_for_event(eventQueue, &e);
		
		if(e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			isGameRunning = false;
		
		//Update display
		game->drawScreen();
	}
	
	//Cleaning
	al_destroy_timer(timer);
    al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	
    return EXIT_SUCCESS;
}

static void *InputThread(ALLEGRO_THREAD *thr, void *arg) {
	Game* game = (Game*)arg;
	ALLEGRO_EVENT_QUEUE *inputQueue;
		
	inputQueue = al_create_event_queue();
	if(!inputQueue) {
		fprintf(stderr, "failed to create inputQueue!\n");
		exit(1);
	}
	
	al_register_event_source(inputQueue, al_get_keyboard_event_source());
	
	while(1) {
		ALLEGRO_EVENT e;
		al_wait_for_event(inputQueue, &e);
		
		if(e.type == ALLEGRO_EVENT_KEY_DOWN || ALLEGRO_EVENT_KEY_UP)
			game->handleInput(e.keyboard);
	}
}

static void* UpdateThread(ALLEGRO_THREAD* thr, void* arg) {
	Game* game = (Game*)arg;
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
	
	while(1) {
		ALLEGRO_EVENT e;
		al_wait_for_event(updateQueue, &e);
		
		if(e.type == ALLEGRO_EVENT_TIMER)
			game->update();
	}
}