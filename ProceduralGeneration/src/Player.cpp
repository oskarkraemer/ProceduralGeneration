#include "Player.h"

void Player::setPosition(sf::Vector2f newPosition) {
	position = newPosition;
	chunkPosition.x = floor(position.x / (chunk_size * tile_size));
	chunkPosition.y = floor(position.y / (chunk_size * tile_size));
	view.setCenter(position);
}

int Player::addToInventory(int tileIndex, int amount) {

	int nextFreeSpace = 0;

	for (int i = 0; i < inventorySlotSize; i++) {
		if (inventory[i][0] == tileIndex && inventory[i][1] < 255) {
			while (inventory[i][1] <= 255 && amount != 0) {
				inventory[i][1]++;
				amount--;

			}
		}
	}

	
	while (amount != 0 && isInventoryFull()==false) {
		for (int i = 0; i < inventorySlotSize; i++) {
			if (inventory[i][0] == 0) {
				nextFreeSpace = i;
				goto outerLoop;
			}
		}

		outerLoop:

		inventory[nextFreeSpace][0] = tileIndex;

		while (inventory[nextFreeSpace][1] <= 255 && amount != 0) {
			inventory[nextFreeSpace][1]++;
			amount--;
		}

		
		
	}

	//Display Inventory
	for (int i = 0; i < inventorySlotSize; i++) {
		std::cout << "[" << i << "] " << "Tile: " << inventory[i][0] << " Amount: " << inventory[i][1] << "\n";
	}

	return amount;
}

int Player::removeFromInventoryAtIndex(int index, int amount) {
	while (inventory[index][1] > 0 && amount!=0) {
		inventory[index][1]--;
		amount--;
	}

	//Display Inventory
	for (int i = 0; i < inventorySlotSize; i++) {
		std::cout << "[" << i << "] " << "Tile: " << inventory[i][0] << " Amount: " << inventory[i][1] << "\n";
	}

	return amount;
}

bool Player::isInventoryFull() {
	bool emptySlot = false;

	for (int i = 0; i < inventorySlotSize; i++) {
		if (inventory[i][0] == 0) {
			emptySlot = true;
		}
	}

	return !emptySlot;
}

void Player::savePlayer() {

	std::ofstream file;
	std::stringstream ss;

	ss << "./world/players/" << uuid << ".player";

	file.open(ss.str());

	file << position.x << '\n';
	file << position.y << '\n';

	for (int i = 0; i < 32; i++) {
		for (int y = 0; y < 2; y++) {
			file << inventory[i][y] << "\n";
		}
	}

	file.close();

	
}

void Player::loadPlayer() {
	std::ifstream file;
	std::stringstream ss;

	std::string line;

	ss << "./world/players/" << uuid << ".player";

	file.open(ss.str());

	if (!file.good()) {
		std::cout << "File opening failed!" << "\n";
	}
	else {
		file >> position.x;

		file >> position.y;
		

		for (int i = 0; i < inventorySlotSize; i++) {
			for (int y = 0; y < 2; y++) {
				file >> inventory[i][y];
				std::cout << inventory[i][y] << '\n';
			}
		}
	}

	file.close();
}