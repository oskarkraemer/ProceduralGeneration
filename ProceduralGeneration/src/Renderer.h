#pragma once
#include "Chunk.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "FPS.h"
#include "World.h"
#include "Console.h"



class Renderer
{

public:
	sf::RenderWindow* window;
	sf::Font font;

	void renderChunkBuffer(World* world);
	sf::Color getTileColor(Chunk* chunk, uint16_t tileIndex);
	void loadChunkVertices(Chunk* chunk);

	void renderPlayer(Player* player);
	void renderChunkBorders(World* world);
	void renderDebugInformation(Player* player, FPS* fps);
	void renderConsole(Console* console);

	Renderer(sf::RenderWindow* cWindow) { window = cWindow; }
};

