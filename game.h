#ifndef GAME_H
#define GAME_H

#include "window.cpp"
#include <SDL.h>
#include "ScreenManager/ScreenManager.h"
#include "ThirdPartyPackages/SDL_FontCache.h"
#include "ThirdPartyPackages/SDL_FontCache.c"

class Game{
	// WINDOW PROPERTIES
	int SCREENWIDTH;
	int SCREENHEIGHT;

	Window window;

	// state of game
	bool running;
	ScreenManager screenManager;

	// Used for processing input
	SDL_Event e;
	int mouseX, mouseY;

	// TIMER
	Uint32 startTime;
	Uint32 now;
	Uint32 deltaT;

	int TICKRATE; // Max ticks per second
	int TICK_DELAY; // 
	int adt; // accumulated deltaT

	FC_Font* debugFont; // Used for debug information 

public:
	Game();

	void processInput();

	void update();
	void render();

	void run();

	SDL_Renderer* getRenderer();

	int* getMouseX(){return &mouseX;};
	int* getMouseY(){return &mouseY;};

private:
	void init();
	void close();

};


#endif //GAME_H