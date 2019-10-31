#include <SDL.h>
#include <iostream>

#include "Constants.cpp"

class Window{
	int width;
	int height;

	SDL_Window* window;

public:
	SDL_Renderer* renderer;


	Window(int width, int height) {
		this->width = width;
		this->height = height;
	}

	bool init(){
		if( SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize.  SDL_ERROR: " << SDL_GetError();
		return false;
		}

		window = SDL_CreateWindow("Lesson 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "Window could not be created. SDL_ERROR: " << SDL_GetError();
			return false;
		}

		SDL_SetWindowResizable(window, SDL_TRUE);


		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetLogicalSize(renderer, CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		return true;

	};

	void close(){
		SDL_DestroyRenderer(renderer);
		renderer = NULL;

		SDL_DestroyWindow(window);
		window = NULL;

		SDL_Quit();
	}

	bool handleEvent(SDL_Event& e){
		if(e.type == SDL_WINDOWEVENT){

			switch(e.window.event){
				case SDL_WINDOWEVENT_SIZE_CHANGED:

					width = e.window.data1;
					height = e.window.data2;
					break;
				case SDL_WINDOWEVENT_EXPOSED:
					break;
			}
			return true;
		}
		return false;
	}



};