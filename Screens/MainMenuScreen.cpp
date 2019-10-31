#include "../ScreenManager/MenuScreen.cpp"

class MainMenuScreen : public MenuScreen{


public:
	MainMenuScreen(std::vector<std::string> entries){
		this->entries = entries;
		selectedEntry = 0;
		size = entries.size();

		//Used to transition menu elements on/off screen
		transitionTime = 1000; // miliseconds
		transitionTimeAccumulator = 0;
		maxTransitionOffset = 570; // Pixels
		transitionOffset = maxTransitionOffset;
	};

	void unloadContent(){};

	// Should match up with order of entries provided in initializer.
	void selectEntry(){
		switch (selectedEntry) {
			case 0: // Create Game
				break;
			case 1: // Join Game
				break;
			case 2: // Practice Mode
				{
				//screenManager->addScreen(new WhateverScreenYouWantToGoTo());
				//screenState = TransitionOff;
				}
				break;
			case 3: // Settings
				break;
			case 4: // Quit Game
				SDL_Event e;
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
				break;

		}
	};
};