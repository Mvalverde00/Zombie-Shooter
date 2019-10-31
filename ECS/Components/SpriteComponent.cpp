#pragma once


struct SpriteComponent {
	SDL_Texture* t;
	SDL_Rect src; // Where the sprite is on the texture

	int width;
	int height;

};