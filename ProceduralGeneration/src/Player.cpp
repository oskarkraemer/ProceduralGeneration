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