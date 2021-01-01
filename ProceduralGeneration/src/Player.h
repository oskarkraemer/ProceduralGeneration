#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Player
{
public:
	sf::Vector2f position{0,0};
	sf::Vector2f chunkPosition = {0, 0};
	sf::Vector2f oldChunkPosition = { 0, 0 };

	void setPosition(sf::Vector2f newPosition);
};

