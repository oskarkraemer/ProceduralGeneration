#include "Player.h"

void Player::setPosition(sf::Vector2f newPosition) {
	position = newPosition;
	chunkPosition.x = floor(position.x / (chunk_size * tile_size));
	chunkPosition.y = floor(position.y / (chunk_size * tile_size));
}