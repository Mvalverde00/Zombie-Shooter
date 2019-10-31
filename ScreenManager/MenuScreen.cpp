//#include "GameScreen.h"
#include "../ThirdPartyPackages/SDL_FontCache.c"
#include <SDL_TTF.h>
#include <string>

#include "../Constants.cpp"

class MenuScreen : public GameScreen{

protected:
	int PADDING; // Pixels between menu options
	//N.B. these should be linked to the values in game.cpp at some point
	const int WIDTH = CONSTANTS::SCREEN_WIDTH;
	const int HEIGHT = CONSTANTS::SCREEN_HEIGHT;

	FC_Font* font;
	FC_Font* selectedFont;  //Font for selected item
	Uint16 entryWidth; //used to width of entry.

	// Used to store options on Menu
	std::vector<std::string> entries;
	int selectedEntry;
	int size;
	int maxWidth = 0;

	SDL_Rect rect; //Used to draw panel behind menu entries.

	//Used for keyboard-based menu navigation.  Use an addative approach so up and down arrows can cancel each other out
	int entryDelta = 0;
	Uint32 changeEntryTimeout = 250; // miliseconds
	Uint32 changeEntryTimeoutAccumulator = 250;
	bool keyDown = false;



public:

	void addEntry(std::string s){
		this->entries.push_back(s);
		size++;
	}


	void loadContent(SDL_Renderer *renderer){
		font = FC_CreateFont();
		FC_LoadFont(font, renderer, "FreeSans.ttf", 30, FC_MakeColor(255,255,255,255), TTF_STYLE_NORMAL); // Init a base font for all Menus

		selectedFont = FC_CreateFont();
		FC_LoadFont(selectedFont, renderer, "FreeSans.ttf", 30, FC_MakeColor(255,0,0,255), TTF_STYLE_NORMAL);

		PADDING = FC_GetLineHeight(font);

		for(std::string entry: entries){
			int width = FC_GetWidth(font,  entry.c_str());
			if (width > maxWidth) maxWidth = width;
		}



	};
	void unloadContent(){
		FC_FreeFont(font);
		FC_FreeFont(selectedFont);
	};

	void processInput(SDL_Event* e){

		if(e->type == SDL_KEYUP) {
			if (e->key.keysym.sym == SDLK_DOWN || e->key.keysym.sym == SDLK_UP) {
				entryDelta = 0;
				keyDown = false;
				changeEntryTimeoutAccumulator = changeEntryTimeout;
			}
		}

		if (e->type == SDL_KEYDOWN) {
			entryDelta = 0;
			keyDown = false;
			switch(e->key.keysym.sym){
				case SDLK_RETURN:
					if(e->key.repeat == 0) selectEntry(); //This should only fire once
					break;
				case SDLK_DOWN:
					std::cout<<"A";
					entryDelta++;
					keyDown = true;
					break;
				case SDLK_UP:
					entryDelta--;
					keyDown = true;
					break;
			}
			
		}
	};

	virtual void selectEntry() {
		// use selectedEntry variable to do something
	}

	void update(Uint32 deltaT){

		updateTransitionSlide(deltaT);

		if(screenState == Active && keyDown == true){
			changeEntryTimeoutAccumulator += deltaT;
			if (changeEntryTimeoutAccumulator > changeEntryTimeout) {
				changeEntryTimeoutAccumulator = 0;


				selectedEntry = ( ((selectedEntry + entryDelta)%size) +size )%size; // This is infuriating, but c++ doesn't 

			}

		}

	};

	void render(SDL_Renderer* renderer){

		//Draw an outline box

		rect.x = (WIDTH-maxWidth)/2 - 10;
		rect.y = 3*PADDING/2 + transitionOffset;
		rect.w = maxWidth + 20;
		rect.h = PADDING * 2*size;

		SDL_SetRenderDrawColor(renderer, 211,211,211, 150);
		SDL_RenderFillRect(renderer, &rect);

		for(int i = 0; i < entries.size(); i++){
			entryWidth = FC_GetWidth(font,  entries[i].c_str());

			//Draw a rect behind it
			rect.x = (WIDTH-entryWidth)/2;
			rect.y = 2*PADDING*(i+1) + transitionOffset;
			rect.w = entryWidth;
			rect.h = PADDING;

			SDL_SetRenderDrawColor(renderer, 0,0,0, 50);
			SDL_RenderFillRect(renderer, &rect);

			if(i == selectedEntry) {
				FC_Draw(selectedFont, renderer, (WIDTH-entryWidth)/2, 2*PADDING*(i+1) + transitionOffset, entries[i].c_str());
			} else{ 
				FC_Draw(font, renderer, (WIDTH-entryWidth)/2, 2*PADDING*(i+1) + transitionOffset, entries[i].c_str());
			}
		}
	};
	
};