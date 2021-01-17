#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "World.h"
#include "Renderer.h"
#include "ChunkLoader.h"
#include "Player.h"

class Mouse
{
private:
	sf::RectangleShape highlightRectangle;

	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;
	sf::Vector2i tilePos;
	sf::Vector2i chunkPos;

	World* world; 
	Renderer* renderer;
	ChunkLoader* chunkLoader;
	Player* player;

public:
	Mouse(World* Cworld, Renderer* Crenderer, ChunkLoader* CchunkLoader, Player* Cplayer) {
		world = Cworld;
		renderer = Crenderer;
		chunkLoader = CchunkLoader;
		player = Cplayer;
	}

	void updateHighlighting(sf::RenderWindow* window);

	void updateBlockBreak();
	void updateBlockPlace();

};

