#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "World.h"
#include "Renderer.h"
#include "ChunkLoader.h"

class Mouse
{
private:
	sf::RectangleShape highlightRectangle;

	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;
	sf::Vector2i tilePos;
	sf::Vector2i chunkPos;

public:
	void updateHighlighting(sf::RenderWindow* window);
	void updateBlockBreak(World* world, Renderer* renderer, ChunkLoader* chunkLoader);

};

