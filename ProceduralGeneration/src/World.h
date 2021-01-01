#pragma once

#include "Chunk.h"
#include <vector>
#include "Globals.h"

class World
{

public:
	//limits in chunks
	int width = 50;
	int height = 50;


	std::vector<Chunk> chunkBuffer;

};

