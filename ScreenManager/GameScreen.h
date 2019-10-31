#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#pragma once
#include "ScreenManager.h"

class ScreenManager;

class GameScreen{
protected:
	enum ScreenState{
		TransitionOn,
		TransitionOff,
		Active,
		Hidden,
	};
	ScreenState screenState = TransitionOn;

	ScreenManager* screenManager;

	int *mouseX, *mouseY;

	// Used to control Transitions
	Uint32 transitionTime; // Time in miliseconds for full transition to occur
	Uint32 transitionTimeAccumulator; // Tracks how far along in transition we are
	int maxTransitionOffset; // Max pixel offset (i.e. fully transition off, should be off screen)
	int transitionOffset; // Tracks current pixel offset

public:
	bool isBlocking = false; // Does this screen block input from screens below it?

	bool hasFocus; // Can this screen accept input?

	void init(ScreenManager* sm);
	virtual void loadContent(SDL_Renderer *renderer) = 0;
	virtual void unloadContent() = 0;

	virtual void processInput(SDL_Event* e) = 0;
	virtual void update(Uint32 deltaT) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

	void updateTransitionSlide(Uint32 deltaT);
};

#endif //GAMESCREEN_H