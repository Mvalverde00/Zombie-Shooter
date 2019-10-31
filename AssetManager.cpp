#pragma once

#include <string>
#include <SDL.h>
#include <map>

class AssetManager {

	std::map<std::string, SDL_Texture*> textures;
	SDL_Renderer* renderer;

	// Is a string already in the map
	bool exists(std::string s) {
		if (textures.find(s) == textures.end()) return false;
		return true;
	}

public:

	AssetManager(SDL_Renderer* r) {
		renderer = r;
	}

	void load(std::string s) {
		// check if already loaded
		if (exists(s)) return;

		// load
		SDL_Surface* surf = IMG_Load(s.c_str());
		if (surf == NULL) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Missing File", "Failed to load a texture.  Please ensure you have all textures downloaded.\n  If this error persists, try redownloading the program.\n", NULL);
			exit(1);
		}

		SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, surf);
		if (t == NULL) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An Error Occured", "Something went wrong.", NULL);
			exit(1);
		}
		SDL_FreeSurface(surf);

		textures.insert({s, t});
	}


	// Returns the texture associated with the given string, or NULL if no such association exists.
	SDL_Texture* get(std::string s) {
		if (exists(s)) return textures[s];
		return NULL;
	}

};