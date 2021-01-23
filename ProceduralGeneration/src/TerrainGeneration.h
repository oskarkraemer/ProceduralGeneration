#pragma once
#include "FastNoiseLite.h"
#include "SFML/Graphics.hpp"
#include <stdlib.h>

#include "Chunk.h"

class TerrainGeneration
{

public:
	float getTile(int x, int y, sf::Vector2f chunkOffset, int seed);
	void generateChunk(Chunk* chunk, int seed);

};

