#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Player
{
public:
	sf::Vector2f position{0,0};
	sf::Vector2f chunkPosition = {0, 0};
	sf::Vector2f oldChunkPosition = { 0, 0 };

	sf::View view;
	
	Player() {
		view.setCenter(position);
		view.setSize(1920, 1080);
	}

	void setPosition(sf::Vector2f newPosition);
};

