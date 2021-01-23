#pragma once

#include "Chunk.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "logging/loguru.hpp"

#include "Globals.h"

class World
{

public:
	//limits in chunks
	int width = 50;
	int height = 50;

	bool loaded = false;

	std::string name;

	std::vector<Chunk> chunkBuffer;

	World(){
		emptyChunkBuffer();	
	}

	
	//Tries to create new World. Returns 1 if failed.
	int createWorld();

	//Clears Chunk Buffer and refills it with fresh Chunks.
	void emptyChunkBuffer();

	// O------------------------------------------------------------------------------O
	// | Saving-Functions                                                             |
	// O------------------------------------------------------------------------------O

	void saveWorld();
	void loadWorld();

};

