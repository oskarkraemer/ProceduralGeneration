#include "Player.h"

void Player::updateMovement(sf::Time deltaTime)
{
	float tempSpeed = deltaTime.asSeconds() * this->movSpeed;
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		//std::cout << "Pressed W" << player.position.y << " "<<player.chunkPosition.y<< std::endl;
		this->setPosition(sf::Vector2f(this->position.x, this->position.y - tempSpeed));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//std::cout << "Pressed D" << player.position.x << " " << player.chunkPosition.x << std::endl;
		this->setPosition(sf::Vector2f(this->position.x + tempSpeed, this->position.y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//std::cout << "Pressed A" << player.position.x << " " << player.chunkPosition.x << std::endl;
		this->setPosition(sf::Vector2f(this->position.x - tempSpeed, this->position.y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		//std::cout << "Pressed S" << player.position.y << " " << player.chunkPosition.y << std::endl;
		this->setPosition(sf::Vector2f(this->position.x, this->position.y + tempSpeed));
	}
}

void Player::setPosition(sf::Vector2f newPosition) {
	int maxPixelSize = Globals::worldSize * Globals::chunk_size * Globals::tile_size;

	if (newPosition.x > -maxPixelSize && newPosition.x < maxPixelSize) {
		if (newPosition.y > -maxPixelSize && newPosition.y < maxPixelSize) {
			position = newPosition;
			chunkPosition.x = floor(position.x / (Globals::chunk_size * Globals::tile_size));
			chunkPosition.y = floor(position.y / (Globals::chunk_size * Globals::tile_size));
			view.setCenter(position);
		}
	}

}

int Player::addToInventory(int tileIndex, int amount) {

	int nextFreeSpace = 0;

	for (int i = 0; i < inventorySlotSize; i++) {
		if (inventory[i][0] == tileIndex && inventory[i][1] < 255) {
			while (inventory[i][1] < 255 && amount != 0) {
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

		while (inventory[nextFreeSpace][1] < 255 && amount != 0) {
			inventory[nextFreeSpace][1]++;
			amount--;
		}
	}


	return amount;
}

int Player::removeFromInventoryAtIndex(int index, int amount) {
	while (inventory[index][1] > 0 && amount!=0) {
		inventory[index][1]--;
		amount--;
		if (inventory[index][1] == 0) {
			inventory[index][0] = 0;
		}
		
	}

	

	return amount;
}

int Player::removeFromInventory(int tileIndex, int amount) {
	for (int i = 0; i < inventorySlotSize && amount !=0; i++) {
		if (inventory[i][0] == tileIndex) {
			inventory[i][1]--;
			amount--;

			//Clear slot
			if (inventory[i][1] == 0) {
				inventory[i][0] = 0;
			}

		}
	}


	return amount;
}

void Player::clearInventory() {
	for (int i = 0; i < inventorySlotSize; i++) {
		inventory[i][0] = 0; inventory[i][1] = 0;
		//std::cout << "["<<i<<"] " << inventory[i][0] << " " << inventory[i][1] << "\n";
	}
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

void Player::savePlayer(World* world) {

	std::ofstream file;
	std::stringstream ss;

	ss << Globals::worldsFolderPath << world->name <<"/players/" << uuid << ".player";

	file.open(ss.str());

	//Save position Vector
	file << position.x << '\n';
	file << position.y << '\n';

	//Save inventory
	for (int i = 0; i < 32; i++) {
		for (int y = 0; y < 2; y++) {
			file << inventory[i][y] << "\n";
		}
	}

	//Save playtime
	updatePlaytime();
	file << playTime << '\n';

	file.close();

	
}

void Player::loadPlayer(World* world) {
	std::ifstream file;
	std::stringstream ss;

	std::string line;

	ss << Globals::worldsFolderPath << world->name <<"/players/" << uuid << ".player";

	file.open(ss.str());

	//Clear Inventory
	clearInventory();

	//Reset position
	setPosition({ 0, 0 });

	if (!file.good()) {
		LOG_F(WARNING, "Player save file could not be loaded!");
	}
	else {
		//Load position Vector
		file >> position.x;
		file >> position.y;
		setPosition(position);
		
		
		//Load inventory


		//Fill inventory with saved items
		for (int i = 0; i < inventorySlotSize; i++) {
			for (int y = 0; y < 2; y++) {
				file >> inventory[i][y];
			}
		}

		//Load playtime
		file >> playTime;

	}
	this->oldChunkPosition.x++;

	file.close();
}

void Player::updatePlaytime() {
	std::chrono::high_resolution_clock::time_point t_end = std::chrono::high_resolution_clock::now();
	playTime += std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start).count();
	t_start = std::chrono::high_resolution_clock::now();
}