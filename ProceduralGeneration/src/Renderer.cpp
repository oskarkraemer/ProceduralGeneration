#include "Renderer.h"
#include "Globals.h"
#include <string>
#include <iostream>

void Renderer::renderChunkBuffer(World* world) {
	for (int i = 0; i < chunkBufferSize; i++) {
		window->draw(world->chunkBuffer[i].vertices);
	}

}

sf::Color Renderer::getTileColor(Chunk* chunk, uint16_t tileIndex) {

	switch ((int)chunk->tileTypes[tileIndex]) {
		case 0:
			//Air
			return sf::Color(sf::Color::Transparent);
		case 1:
			//Green
			return sf::Color(sf::Color(54, 110, 71));
		case 2:
			//Red
			return sf::Color(sf::Color(110, 57, 54));
		case 3:
			//Blue
			return sf::Color(sf::Color(54, 68, 110));
		case 4:
			//Yellow
			return sf::Color(sf::Color(139, 140, 52));
	}
}

void Renderer::loadChunkVertices(Chunk* chunk) {
	int Xoff = chunk->x * (chunk_size * tile_size);
	int Yoff = chunk->y * (chunk_size * tile_size);

	
	chunk->vertices.setPrimitiveType(sf::Quads);
	chunk->vertices.resize(chunk_size * chunk_size * 4);


	for (int y = 0; y < chunk_size; y++) {
		for (int x = 0; x < chunk_size; x++) {
			sf::Vertex* quad = &chunk->vertices[(y * chunk_size + x) * 4];
			sf::Color color = getTileColor(chunk, y * chunk_size + x);


			quad[0].position = sf::Vector2f(x * tile_size + Xoff, y * tile_size + Yoff);
			quad[1].position = sf::Vector2f((x + 1) * tile_size + Xoff, y * tile_size + Yoff);
			quad[2].position = sf::Vector2f((x + 1) * tile_size + Xoff, (y + 1) * tile_size + Yoff);
			quad[3].position = sf::Vector2f(x * tile_size + Xoff, (y + 1) * tile_size + Yoff);

			quad[0].color = color;
			quad[1].color = color;
			quad[2].color = color;
			quad[3].color = color;

			
		}
	}
}

void Renderer::renderPlayer(Player* player) {
	sf::CircleShape circle;
	circle.setRadius(20);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(player->position);

	window->draw(circle);
}

void Renderer::renderChunkBorders(World* world) {
	sf::RectangleShape rectangle(sf::Vector2f(1024, 1024));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(1);

	for (int i = 0; i < chunkBufferSize; i++) {
		rectangle.setPosition(world->chunkBuffer[i].x * 1024, world->chunkBuffer[i].y * 1024);
		window->draw(rectangle);
	}
}

int Renderer::renderDebugInformation(Player* player ,FPS* fps) {
	sf::Font font;
	sf::Text text;

	if (!font.loadFromFile("./res/Roboto-Regular.ttf")) {
		return 1;
	}

	text.setFont(font);
	text.setString("FPS: " + std::to_string(fps->getFPS()) + "\n"
				+ "X: " + std::to_string(player->position.x) + " Y: " + std::to_string(player->position.y) + "\n"
				+ "Cx: " + std::to_string(player->chunkPosition.x) + " Cy: " + std::to_string(player->chunkPosition.y) + "\n"
				+ "ChunkBuffer size: " + std::to_string(chunkBufferSize));

	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);

	window->draw(text);

}