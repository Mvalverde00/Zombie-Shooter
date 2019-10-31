#ifndef CONSTANTS_GUARD
#define CONSTANTS_GUARD

#include <SDL.h>
#include <array>



struct CONSTANTS {
	// The initial screen width and height, as well as the internal virtual screen dimensions, regardless of what the window is resized to.
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static const int TILE_WIDTH = 32;
	static const int TILE_HEIGHT = 32;

};




#endif //Constants