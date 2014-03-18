ButtGame

The best game

The only game

_BUTT_ lyfe

Right now, to compile you have to have Allegro 5 installed on your system
Get that done, get it, ya girl, get it.

Then if you're on a unix based OS you can gcc it like dis:

g++ main.cpp Game.cpp GenericView.cpp SquareView.cpp GenericEnemy.cpp Player.cpp -lAllegro -lAllegro_main -lAllegro_primitives

Obviously more source files will be added overtime, so include those in your build as well. Someday we'll get around to making a makefile. Not sure how well this will compile on windows. It should definitely be possible because Allegro is crossplatform.