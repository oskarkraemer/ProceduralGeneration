#pragma once

#include "Chunk.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "logging/loguru.hpp"
#include <limits>
#include <iostream>
#include <random>

#include "Globals.h"

class World
{

public:

	bool loaded = false;

	std::string name;

	std::vector<Chunk> chunkBuffer;
	unsigned int seed = 0;

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

