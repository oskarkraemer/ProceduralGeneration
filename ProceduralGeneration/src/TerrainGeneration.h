#pragma once
#include "PerlinNoise.h"
#include "SFML/Graphics.hpp"
#include <stdlib.h>

#include "Chunk.h"

class TerrainGeneration
{

public:
	float getTile(int x, int y, sf::Vector2f chunkOffset);
	void generateChunk(Chunk* chunk, int seed);

};

