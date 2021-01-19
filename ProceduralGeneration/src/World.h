#pragma once

#include "Chunk.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>

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
	
	//Tries to create new World. Returns 1 if failed.
	int createWorld();

	// O------------------------------------------------------------------------------O
	// | Saving-Functions                                                             |
	// O------------------------------------------------------------------------------O

	void saveWorld();
	void loadWorld();

};

