#include "ScreenManager.h"

#include "GameScreen.cpp"


void ScreenManager::render(SDL_Renderer* renderer){
	for (GameScreen *screen : screens){
		screen->render(renderer);
	}
};

void ScreenManager::update(Uint32 deltaT, int* mouseX, int* mouseY){
	for(GameScreen *screen : screens){
		screen->update(deltaT);
	}
};

void ScreenManager::processInput(SDL_Event* e){
	for(int i = screens.size()-1; i >= 0; i--){
		GameScreen *screen = screens[i];

		screen->processInput(e);

		// Break out early if we encounter a blocking screen
		if (screen->isBlocking){
			break;
		}

	}
}

ScreenManager::ScreenManager(Game *game){
	this->game = game;
};

void ScreenManager::addScreen(GameScreen *screen){
	screens.push_back(screen);
	screen->init(this);
};

void ScreenManager::removeScreen(GameScreen *screen) {

	std::vector<GameScreen*>::iterator it;
	for (it = screens.begin(); it != screens.end(); ) {
		if (*it == screen) {
			delete *it; delete screen;
			it = screens.erase(it);
		} else {++it;}
	}
};

void ScreenManager::init(SDL_Renderer *renderer){
};

void ScreenManager::cleanup(){

};