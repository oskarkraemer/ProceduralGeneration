#pragma once
#include "Chunk.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "FPS.h"
#include "World.h"



class Renderer
{

public:
	sf::RenderWindow* window;

	void renderChunkBuffer(World* world);
	sf::Color getTileColor(Chunk* chunk, uint8_t tileIndex);
	void loadChunkVertices(Chunk* chunk);

	void renderPlayer(Player* player);
	void renderChunkBorders();
	int renderFPS(FPS* fps);

	Renderer(sf::RenderWindow* cWindow) { window = cWindow; }
};
