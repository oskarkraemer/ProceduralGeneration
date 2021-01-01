#include "TerrainGeneration.h"
#include "Globals.h"
#include <iostream>

float TerrainGeneration::getTile(int x, int y)
{
	PerlinNoise pn;
	float scale = 1.f;


	double xCoord = (double)x /  scale;
	double yCoord = (double)y /  scale;



	return pn.noise(xCoord, yCoord, 0);
}

void TerrainGeneration::generateChunk(Chunk* chunk, int seed) {
	srand(seed);

	for (int y = 0; y < chunk_size; y++) {
		for (int x = 0; x < chunk_size; x++) {
			chunk->tileTypes[y * chunk_size + x] = 1 + (rand() % 4);
		}
	}

}