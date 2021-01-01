#pragma once
#include "Player.h"
#include "Renderer.h"
#include "World.h"
#include "TerrainGeneration.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ChunkLoader
{
private:
	World* world;
	Renderer* renderer;
	TerrainGeneration* terrainGenerator;

public:
	//Load Chunks near the Player
	void loadChunksToBuffer(Player* player, bool existsInBufferCheck);

	//Saves Chunk to .chunk File
	void saveChunkToFile(Chunk* chunk);

	//Loads Chunk from .chunk File
	Chunk loadChunkFromFile(int x, int y);

	ChunkLoader(World* cWorld, Renderer* cRenderer, TerrainGeneration* cTerrainGenerator) { world = cWorld;  renderer = cRenderer; terrainGenerator = cTerrainGenerator; }
};

