#pragma once

#include <SDL.h>
#include "../../Vector2D.cpp"

struct PlayerMovementInputComponent {
	int speed;
	Vector2D dir;
	const Uint8* state = SDL_GetKeyboardState(NULL);

};