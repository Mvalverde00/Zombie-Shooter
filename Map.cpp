#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SDL.h>
#include <map>

#include "Camera.cpp"

class Map {

	// A 2D array of integers which describes the map
	std::vector<std::vector<uint8_t>> map;

	// An array of integers specifying which tiles from the tileset have been used, and thus, which need to be loaded into memory.
	std::vector<bool> usedTiles;

	// fname_map contains the arrangement of tiles that defines the map; fname_tileset contains all of the tiles to be used in the map
	std::string fname_map;
	std::string fname_tileset;

	// Map tile IDs to tile textures
	std::map<uint8_t, SDL_Texture*> t_textures;

	// Tile width and height
	int t_width = CONSTANTS::TILE_WIDTH;
	int t_height = CONSTANTS::TILE_HEIGHT;

	void loadMap(){
		std::ifstream file;
		std::string line;
		std::vector<uint8_t> row;

		// Open the map and check that it exists
		file.open(fname_map);
		if (!file) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Missing File", "Failed to load the map.  Please ensure you have the map downloaded.\n  If this error persists, try redownloading the program.\n", NULL);
			exit(1);
		}

		// Iterate over every line in the file
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string line_stream;

			// Iterate over a given line, in batches separated by spaces.  Convert each batch to an int, then push it into the row.
			while(std::getline(iss, line_stream, ' ')) {
				row.push_back(std::stoi(line_stream));
				usedTiles[std::stoi(line_stream)] = true;
			}

			// Add the row to the map, then clear the row to prepare for the next iteration
			map.push_back(row);
			row.clear();
		}
		// Close the file now that we are done
		file.close();
	}


	void loadTiles(SDL_Renderer* renderer){
		SDL_Surface* tileset_surf = IMG_Load(fname_tileset.c_str());
		if (tileset_surf == NULL) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Missing File", "Failed to load the tileset.  Please ensure you have the tileset downloaded.\n  If this error persists, try redownloading the program.\n", NULL);
			exit(1);
		}

		SDL_Texture* tileset = SDL_CreateTextureFromSurface(renderer, tileset_surf);
		if (tileset == NULL) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An Error Occured", "Something went wrong.", NULL);
			exit(1);
		}
		SDL_FreeSurface(tileset_surf);


		////// Prepare to load the tiles //////////

		// Get texture width and height, in pixels
		int pWidth, pHeight;
		SDL_QueryTexture(tileset, NULL, NULL, &pWidth, &pHeight);

		// The textures width, in tiles
		int tilesInARow = pWidth/t_width;
		// Store the current render target.  To copy the textures over, we will need to change the render's target.  We want to set it back to whatever it was
		// after we are done.
		SDL_Texture* original_target = SDL_GetRenderTarget(renderer);

		// Check all the usedTiles.  If a tile is used, load it.
		for(int i = 0; i <usedTiles.size(); i++) {
			if (usedTiles[i] == true) {
				int x = i % (tilesInARow);
				int y = i/(tilesInARow);

				std::cout<< "Loading Tile at: ("<<x<<", "<<y<<")\n";

				// Create a blank texture
				SDL_Texture* t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, t_width, t_height);

				// Set the blank texture as the target, then copy the relevent tile. 
				SDL_SetRenderTarget(renderer, t);
				SDL_Rect src = {x*t_width, y*t_height, t_width, t_height};
				SDL_RenderCopy(renderer, tileset, &src, NULL);

				// Add the texture to the map of textures
				t_textures.insert({i, t});

			}
		}

		// Cleanup- free the texture from memory, and return the renderer to its original target.
		SDL_DestroyTexture(tileset);
		SDL_SetRenderTarget(renderer, original_target);

	}


public:
	// Total Map width/height
	int WIDTH, HEIGHT;

	Map(std::string fname_map, std::string fname_tileset) {
		this->fname_map = fname_map;
		this->fname_tileset = fname_tileset;

		// Populate the usedTiles vector will all values set to false.
		this->usedTiles.resize(256, false);
	}

	void loadContent(SDL_Renderer* renderer) {

		this->loadMap();

		// Log the map in console, for error purposes.
		/*for (std::vector<uint8_t> v : this->map){
				for(uint8_t i : v) {
					std::cout<< +i;
					std::cout<< ", ";}
				std::cout<<"\n";
			}
		*/

		this->loadTiles(renderer);

		// Set the world width and world height.
		WIDTH = map[0].size()*t_width;
		HEIGHT = map.size()*t_height;

		std::cout<<"WORLD SIZE: "<<WIDTH<<", "<<HEIGHT;
	};


	void unloadContent() {
		for (std::map<uint8_t, SDL_Texture*>::iterator it=t_textures.begin(); it!=t_textures.end(); ++it) {
			SDL_DestroyTexture(it->second);
		}
	};

	void render(SDL_Renderer* renderer, Camera* cam) {
		SDL_Rect dest;
		Vector2D top_left = cam->getPos();
		Vector2D bottom_right = cam->getBR();

		int top_left_tile[2] = {top_left.x/t_width, top_left.y/t_height};
		int bottom_right_tile[2] = {bottom_right.x/t_width, bottom_right.y/t_height};


		for (int y = top_left_tile[1]; y < bottom_right_tile[1] + 1; y++) {
			for (int x = top_left_tile[0]; x < bottom_right_tile[0] + 1; x++) {
				//dest = {(x-top_left_tile[0])*t_width, (y-top_left_tile[1])*t_width, t_width, t_height};
				dest = {(x*t_width)-top_left.x, (y*t_width)-top_left.y, t_width, t_height};
				SDL_RenderCopy(renderer, t_textures[map[y][x]], NULL, &dest );
			}
		}
	}


};