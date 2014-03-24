//
//  GameDefines.h
//  ButtGame
//
//  Created by tim on 3/18/14.
//  Copyright (c) 2014 _BUTT_. All rights reserved.
//

#ifndef ButtGame_GameDefines_h
#define ButtGame_GameDefines_h

//HD AS FUCK
#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080
#define LOGIC_FPS 128.f
#define INPUT_FPS 128.f

#define kLogicTick 1.f / LOGIC_FPS
#define kVelocityIterations 8
#define kPositionIterations 3

#define kMetersToPixels 100.f
#define kMetersFromPixels(x) (float)x / kMetersToPixels
#define kPixelsFromMeters(x) (float)x * kMetersToPixels

#define kDefaultXSpeed 1.5f
#define kDefaultYSpeed 1.5f
#define kDefaultLinearDampening 8.f
#define kDefaultAngularDampening 1.f

#define kPlayerSize 30
#define kPlayerHitboxSize 22

#define DEBUG 1

#endif
