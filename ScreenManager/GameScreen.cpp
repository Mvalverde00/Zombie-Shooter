
#include "GameScreen.h"
#include <SDL.h>

// Perform general initializations, then allow for screen-specific inits through loadContent function.
void GameScreen::init(ScreenManager* sm){
	screenManager = sm; 

	mouseX = screenManager->game->getMouseX();
	mouseY = screenManager->game->getMouseY();

	loadContent(sm->game->getRenderer());

};

void GameScreen::updateTransitionSlide(Uint32 deltaT) {
	if (screenState == TransitionOn){

			transitionTimeAccumulator += deltaT;
			transitionOffset = (1 - ((float)transitionTimeAccumulator/transitionTime))  * maxTransitionOffset; // make it negative so it goes up

			if (transitionTimeAccumulator >= transitionTime) {
				screenState = Active;
			}

		}

		if(screenState == TransitionOff){
			transitionTimeAccumulator -= deltaT;
			transitionOffset = -(1 - ((float)transitionTimeAccumulator/transitionTime))  * maxTransitionOffset;

			if(transitionTimeAccumulator <= 0) {
				screenManager->removeScreen(this);
			}

		}

}

//int* GameScreen::mouseX = screenManager->game->getMouseX();