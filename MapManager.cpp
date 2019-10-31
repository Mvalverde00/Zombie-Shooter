#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class MapManager {

	// A 2D array of integers which describes the map
	std::vector<std::vector<uint8_t>> map;

	// An array of SDL_Rects, outling a tile texture in the tilemap. Their indices correspend to the integers in the map.
	std::vector<SDL_Rect> tile_texture_rects;

	// A texture containing the entire tilemap.
	SDL_Texture* tilemap_texture;

	int tWidth = CONSTANTS::TILE_WIDTH;
	int tHeight = CONSTANTS::TILE_HEIGHT;

public:

	// Load a map from supplied filename into byte array
	// fname_map contains the actual map itself; fname_t_mapper contains the data for mapper tiles to integers; fname_t_map contains the tilemap.
	MapManager(std::string fname_map, std::string fname_t_mapper, std::string fname_t_map) {
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
				}

				// Add the row to the map, then clear the row to prepare for the next iteration
				map.push_back(row);
				row.clear();
			}
			// Close the file now that we are done
			file.close();

			///////			DEBUG			/////////
			for (std::vector<uint8_t> v : map){
				for(uint8_t i : v) {
					std::cout<< +i;
					std::cout<< ", ";}
				std::cout<<"\n";
			}

			// Open the tile mapper and check that it exists
			file.open(fname_t_mapper);
			if (!file) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Missing File", "Failed to load the map.  Please ensure you have the map downloaded.\n  If this error persists, try redownloading the program.\n", NULL);
				exit(1);
			}

			while(std::getline(file, line)) {
				std::istringstream iss(line);
				std::string line_stream;

				while(std::getline(iss, line_stream, ' ')) {
					row.push_back(std::stoi(line_stream));
				}
				tile_texture_rects.push_back( SDL_Rect {row[0], row[1], row[2], row[3]} );
				row.clear();

			}


	}


	void render(SDL_Renderer* renderer){

		for(int y = 0; y < map.size(); y++) {
			for (int x = 0; x < map[y].size(); x++) {
				SDL_RenderCopy(renderer, tTextures[0], NULL, NULL);
			}
		}

	};


};