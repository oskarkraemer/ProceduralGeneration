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
	sf::Color getTileColor(uint8_t tileIndex);
	void loadChunkVertices(Chunk* chunk);

	void renderPlayer(Player* player);
	void renderChunkBorders(World* world);
	void renderDebugInformation(Player* player, FPS* fps);
	void renderConsole(Console* console);
	void renderHotbar(Player* player);

	Renderer(sf::RenderWindow* cWindow) { window = cWindow; }
};

