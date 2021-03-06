#pragma once
#include <stdint.h>
#include <string>

namespace Globals {
	//Number of tiles in chunk
	extern uint8_t chunk_size;

	//Number of pixels in each tile
	extern uint8_t tile_size;

	//Radius in which chunks are loaded
	extern uint8_t load_radius;

	//number of chunks in buffer
	extern int chunkBufferSize;

	//is Window fullscreen
	extern bool isFullscreen;

	//path to the worlds folder
	extern std::string worldsFolderPath;

	//world limit in chunks
	extern int worldSize;

	//tiles enum
	extern enum Tile {
		AIR, GRASS, STONE, WATER, SAND
	};
}