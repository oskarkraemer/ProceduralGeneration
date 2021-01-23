#include "Renderer.h"
#include "Globals.h"


void Renderer::renderChunkBuffer(World* world) {
	for (int i = 0; i < Globals::chunkBufferSize; i++) {
		window->draw(world->chunkBuffer[i].vertices);
	}

}

sf::Color Renderer::getTileColor(uint8_t tileID) {

	switch ((int)tileID) {
		case 0:
			//Air
			return sf::Color(sf::Color(26, 13, 0));
		case 1:
			//Grass
			return sf::Color(sf::Color(54, 110, 71));
		case 2:
			//Stone
			return sf::Color(sf::Color(51, 51, 51));
		case 3:
			//Blue
			return sf::Color(sf::Color(54, 68, 110));
		case 4:
			//Yellow
			return sf::Color(sf::Color(139, 140, 52));
	}
}

void Renderer::loadChunkVertices(Chunk* chunk) {
	int Xoff = chunk->x * (Globals::chunk_size * Globals::tile_size);
	int Yoff = chunk->y * (Globals::chunk_size * Globals::tile_size);

	
	chunk->vertices.setPrimitiveType(sf::Quads);
	chunk->vertices.resize(Globals::chunk_size * Globals::chunk_size * 4);


	for (int y = 0; y < Globals::chunk_size; y++) {
		for (int x = 0; x < Globals::chunk_size; x++) {
			sf::Vertex* quad = &chunk->vertices[(y * Globals::chunk_size + x) * 4];
			sf::Color color = getTileColor(chunk->tileTypes[y * Globals::chunk_size + x]);


			quad[0].position = sf::Vector2f(x * Globals::tile_size + Xoff, y * Globals::tile_size + Yoff);
			quad[1].position = sf::Vector2f((x + 1) * Globals::tile_size + Xoff, y * Globals::tile_size + Yoff);
			quad[2].position = sf::Vector2f((x + 1) * Globals::tile_size + Xoff, (y + 1) * Globals::tile_size + Yoff);
			quad[3].position = sf::Vector2f(x * Globals::tile_size + Xoff, (y + 1) * Globals::tile_size + Yoff);

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
	int chunkPixelSize = Globals::chunk_size * Globals::tile_size;

	sf::RectangleShape rectangle(sf::Vector2f(chunkPixelSize, chunkPixelSize));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(1);

	for (int i = 0; i < Globals::chunkBufferSize; i++) {
		rectangle.setPosition(world->chunkBuffer[i].x * chunkPixelSize, world->chunkBuffer[i].y * chunkPixelSize);
		window->draw(rectangle);
	}
}

void Renderer::renderDebugInformation(Player* player ,FPS* fps) {
	sf::Text text;

	text.setFont(font);
	text.setString("Name: " + player->name + " UUID: " + player->uuid + "\n"
				+ "FPS: " + std::to_string(fps->getFPS()) + "\n"
				+ "X: " + std::to_string(player->position.x) + " Y: " + std::to_string(player->position.y) + "\n"
				+ "Cx: " + std::to_string(player->chunkPosition.x) + " Cy: " + std::to_string(player->chunkPosition.y) + "\n"
				+ "ChunkBuffer size: " + std::to_string(Globals::chunkBufferSize));

	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);

	window->draw(text);

}

void Renderer::renderConsole(Console* console) {
	sf::RectangleShape rectangle(sf::Vector2f(window->getSize().x, 30));

	sf::Text text;
	text.setFont(font);
	text.setString(console->input);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	rectangle.setPosition(0, window->getSize().y-30);
	text.setPosition(0, window->getSize().y - 30);
	
	rectangle.setFillColor(sf::Color(sf::Color(0, 0, 0, 128)));

	window->draw(rectangle);
	window->draw(text);
}

void Renderer::renderHotbar(Player* player) {
	sf::RectangleShape hotbarRectangle(sf::Vector2f(64, 64));
	sf::RectangleShape itemRectangle(sf::Vector2f(48, 48));
	sf::RectangleShape selectedRectangle(sf::Vector2f(64, 64));

	hotbarRectangle.setFillColor(sf::Color(0, 0, 0, 128));
	hotbarRectangle.setOutlineThickness(1);
	hotbarRectangle.setOutlineColor(sf::Color::Black);

	if (player->name == "PizzaHannes") {
		selectedRectangle.setOutlineColor(sf::Color(218, 165, 32));
	}
	else {
		selectedRectangle.setOutlineColor(sf::Color::Red);
	}
	
	selectedRectangle.setOutlineThickness(2);
	selectedRectangle.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < 8; i++) {
		hotbarRectangle.setPosition(window->getSize().x / 2 -320 + (i*74), window->getSize().y - 74);
		window->draw(hotbarRectangle);

		if (player->selectedItem == i) {
			selectedRectangle.setPosition(window->getSize().x / 2 - 320 + (i * 74), window->getSize().y - 74);
			window->draw(selectedRectangle);
		}

		if ((int)player->inventory[i][0] != 0) {
			itemRectangle.setFillColor(getTileColor((int)player->inventory[i][0]));
			itemRectangle.setPosition(window->getSize().x / 2 - 320 + (i * 74) + 8, window->getSize().y - 74 + 8);
			window->draw(itemRectangle);
		}
	}

	
}

//Constructor
Renderer::Renderer(sf::RenderWindow* cWindow)
{
	this->window = cWindow;
	if (!font.loadFromFile("./res/Roboto-Regular.ttf")) {
		LOG_F(ERROR, "Font could not be loaded!");
	}
}
