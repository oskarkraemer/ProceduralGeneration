#include "TerrainGeneration.h"
#include "Globals.h"
#include <iostream>

int TerrainGeneration::getTile(int x, int y, sf::Vector2f chunkOffset, int seed)
{


	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetSeed(seed);
	
	
	float scale = 2.f;

	int xoff = chunkOffset.x * Globals::chunk_size;
	int yoff = chunkOffset.y * Globals::chunk_size;


	int xCoord = x + xoff;
	int yCoord = y + yoff;
	
	float noise_value = noise.GetNoise((float)xCoord, (float)yCoord);

	//map different blocks to perlin value
	if (noise_value < 0.3) {
		return Globals::Tile::WATER; // WATER
	} 
	else if (noise_value < 0.4) {
		return Globals::Tile::SAND; // SAND
	}
	else if (noise_value < 0.8) {
		return Globals::Tile::GRASS; // GRASS
	}
	else {
		return Globals::Tile::STONE; // STONE
	}


}

void TerrainGeneration::generateChunk(Chunk* chunk, int seed) {
	
	for (int y = 0; y < Globals::chunk_size; y++) {
		for (int x = 0; x < Globals::chunk_size; x++) {
			//std::cout << y * chunk_size + x << std::endl;
			chunk->tileTypes[y * Globals::chunk_size + x] = getTile(x, y, sf::Vector2f(chunk->x, chunk->y), seed);
		}
	}

}