#include "TerrainGeneration.h"
#include "Globals.h"
#include <iostream>

float TerrainGeneration::getTile(int x, int y, sf::Vector2f chunkOffset)
{

	//1+ (rand()%4)

	PerlinNoise pn;
	float scale = 2.f;

	int xoff = chunkOffset.x * Globals::chunk_size;
	int yoff = chunkOffset.y * Globals::chunk_size;

	

	//double xCoord = (double)x / (double)chunk_size * scale + ((double)chunkOffset.x * (double)chunk_size);
	//double yCoord = (double)y / (double)chunk_size * scale + ((double)chunkOffset.y * (double)chunk_size);

	double xCoord = (double)x  / (double)Globals::chunk_size * scale + xoff;
	double yCoord = (double)y  / (double)Globals::chunk_size * scale + yoff;
	
	float noise = pn.noise(xCoord, yCoord, 0);

	//map different blocks to perlin value
	if (noise < 0.3) {
		return 3; // WATER
	} 
	else if (noise < 0.35) {
		return 4; // SAND
	}
	else if (noise < 0.7) {
		return 1; // GRASS
	}
	else {
		return 2; // STONE
	}


}

void TerrainGeneration::generateChunk(Chunk* chunk, int seed) {
	srand(seed);


	for (int y = 0; y < Globals::chunk_size; y++) {
		for (int x = 0; x < Globals::chunk_size; x++) {
			//std::cout << y * chunk_size + x << std::endl;
			chunk->tileTypes[y * Globals::chunk_size + x] = getTile(x, y, sf::Vector2f(chunk->x, chunk->y));
		}
	}

}