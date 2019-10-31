#include <SDL.h>
#include <SDL_TTF.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "game.h"

#include "ScreenManager/ScreenManager.cpp"
#include "Screens/GameplayScreen.cpp"
#include "Constants.cpp"

Game::Game() : window{CONSTANTS::SCREEN_WIDTH,CONSTANTS::SCREEN_HEIGHT}, screenManager{this}{
	SCREENWIDTH = CONSTANTS::SCREEN_WIDTH;
	SCREENHEIGHT = CONSTANTS::SCREEN_HEIGHT;

	TICKRATE = 60;
	TICK_DELAY = 1000/TICKRATE;
	adt = 0;
}

void Game::processInput(){
	while(SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT){
			running = false;
		}
		else if (window.handleEvent(e)){continue;} // Dont pass the event on if it was a window.
		else if (e.type == SDL_MOUSEMOTION){mouseX = e.motion.x; mouseY = e.motion.y;}
		else {
			screenManager.processInput(&e);
		}
	}
};

void Game::update(){
	now = SDL_GetTicks();
	deltaT = now - startTime;
	startTime = now;

	adt += deltaT;
	if (adt >= TICK_DELAY){
		adt -= TICK_DELAY;
		screenManager.update(TICK_DELAY, &mouseX, &mouseY);
	}

}

void Game::render(){
	SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(window.renderer);

	screenManager.render(window.renderer);

	// FPS
	FC_Draw(debugFont, window.renderer, 100, CONSTANTS::SCREEN_HEIGHT - 100, std::to_string(deltaT).c_str());
	int fps;
	if (deltaT == 0) {fps = 1000;} else{fps = 1000/deltaT;}
	FC_Draw(debugFont, window.renderer, 100, CONSTANTS::SCREEN_HEIGHT - 50, std::to_string(fps).c_str());


	SDL_RenderPresent(window.renderer);
};

void Game::run() {
	running = true;
	init();

	while (running) {
		//std::cout<<"PROCESSING";
		processInput();
		//std::cout<<"UPDATING";
		update();
		//std::cout<<"RENDERING\n";
		render();
	}

	close();
}

SDL_Renderer* Game::getRenderer(){
	return window.renderer;
}

void Game::init(){
	window.init(); // Create a window and set its resolution
	SDL_RenderSetLogicalSize(window.renderer, SCREENWIDTH, SCREENHEIGHT);

	startTime = SDL_GetTicks(); // Start the main clock

	IMG_Init(IMG_INIT_PNG);

	TTF_Init();// Init fonts

	debugFont = FC_CreateFont();
	FC_LoadFont(debugFont, window.renderer, "FreeSans.ttf", 15, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL); 



	// Push all initial screens.
	//screenManager.addScreen(new MainMenuScreen{std::vector<std::string> {"Create game", "Join game", "Practice", "Settings", "Quit Game"}} );
	screenManager.addScreen(new GameplayScreen{} );
	//screenManager.addScreen(etc.);

	screenManager.init(window.renderer); // Load screens

	SDL_version compiled;
	SDL_VERSION(&compiled);
	SDL_version linked;
	SDL_GetVersion(&linked);

	//std::cout<<"COMPILED: " << compiled.major <<"."<<compiled.minor<<"."<<compiled.patch<<"\n";
	//std::cout<<"LINKED: " << linked.major <<"."<<linked.minor<<"."<<linked.patch<<"\n";
	printf("We compiled against SDL version %d.%d.%d ...\n",
       compiled.major, compiled.minor, compiled.patch);
	printf("But we are linking against SDL version %d.%d.%d.\n",
       linked.major, linked.minor, linked.patch);


}

void Game::close(){

	screenManager.cleanup();
	window.close();
}
