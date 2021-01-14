#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <stdint.h>

#include <iostream>

class Player
{
public:
	sf::Vector2f position{0,0};
	sf::Vector2f chunkPosition = {0, 0};
	sf::Vector2f oldChunkPosition = { 0, 0 };

	sf::View view;

	int inventory[32][2] = { 0 };
	int inventorySlotSize = 32;

	Player() {
		view.setCenter(position);
		view.setSize(1920, 1080);
	}

	//Inventory functions

	//Adds amount of tiles to inventory. Returns remaining items.
	int addToInventory(int tileIndex, int amount);

	//Removes a specific amount of items at a given index. Returns remaining amount.
	int removeFromInventoryAtIndex(int index, int amount);

	//Returns bool if the inventory is full.
	bool isInventoryFull();

	void setPosition(sf::Vector2f newPosition);
};

