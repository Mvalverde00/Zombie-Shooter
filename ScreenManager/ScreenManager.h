#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include "GameScreen.h"
#include "../game.h"

#pragma once
#include <vector>

class GameScreen;
class Game;

class ScreenManager{
	std::vector<GameScreen*> screens;

public:
	Game *game;

	ScreenManager(Game *game);

	void render(SDL_Renderer* renderer);
	void update(Uint32 deltaT, int* mouseX, int* mouseY);
	void processInput(SDL_Event* e);

	void addScreen(GameScreen *screen);
	void removeScreen(GameScreen *screen);

	void init(SDL_Renderer *renderer);
	void cleanup();

};

#endif //SCREENMANAGER_H