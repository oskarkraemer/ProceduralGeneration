#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "World.h"
#include "picosha2.h"
#include <stdint.h>
#include "logging/loguru.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

class Player
{
public:
	std::string name;
	std::string uuid;


	//Position data
	sf::Vector2f position{0,0};
	sf::Vector2f chunkPosition = {0, 0};
	sf::Vector2f oldChunkPosition = { 1, 1 };

	sf::View view;

	//Inventory data
	int inventory[32][2] = { 0 };
	int inventorySlotSize = 32;
	int selectedItem = 0;

	//Playtime data
	uint32_t playTime = 0;
	std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();

	//Movement variables
	int movSpeed = 800;


	Player(std::string Cname) {
		name = Cname;
		picosha2::hash256_hex_string(name, uuid);

		view.setCenter(position);
		view.setSize(1920, 1080);
	}

	// O------------------------------------------------------------------------------O
	// | Inventory-Functions                                                          |
	// O------------------------------------------------------------------------------O

	//Adds amount of tiles to inventory. Returns remaining items.
	int addToInventory(int tileIndex, int amount);

	//Removes a specific amount of items at a given index. Returns remaining amount.
	int removeFromInventoryAtIndex(int index, int amount);

	//Removes a specific amount of items. Returns remaining amount.
	int removeFromInventory(int tileIndex, int amount);

	//Clears inventory
	void clearInventory();

	//Returns bool if the inventory is full.
	bool isInventoryFull();

	// O------------------------------------------------------------------------------O
	// | Position-Functions                                                           |
	// O------------------------------------------------------------------------------O

	void updateMovement(sf::Time deltaTime);
	void setPosition(sf::Vector2f newPosition);

	// O------------------------------------------------------------------------------O
	// | Saving-Functions                                                             |
	// O------------------------------------------------------------------------------O

	void savePlayer(World* world);
	void loadPlayer(World* world);

	// O------------------------------------------------------------------------------O
	// | Playtime-Functions                                                           |
	// O------------------------------------------------------------------------------O

	void updatePlaytime();

};

