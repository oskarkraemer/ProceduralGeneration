#include "Renderer.h"
#include "Globals.h"


void Renderer::renderChunkBuffer(World* world) {
	for (int i = 0; i < Globals::chunkBufferSize; i++) {
		window->draw(world->chunkBuffer[i].vertices);
	}

}

sf::Color Renderer::getTileColor(uint8_t tileID) {

	switch ((int)tileID) {
		case Globals::Tile::AIR:
			//Air
			return sf::Color(sf::Color(26, 13, 0));
		case Globals::Tile::GRASS:
			//Grass
			return sf::Color(sf::Color(54, 110, 71));
		case Globals::Tile::STONE:
			//Stone
			return sf::Color(sf::Color(51, 51, 51));
		case Globals::Tile::WATER:
			//Water
			return sf::Color(sf::Color(54, 68, 110));
		case Globals::Tile::SAND:
			//Sand
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

void Renderer::renderDebugInformation(Player* player, FPS* fps, Console* console) {
	sf::Text text;

	text.setFont(font);
	text.setString("Name: " + player->name + " UUID: " + player->uuid + "\n"
				+ "FPS: " + std::to_string(fps->getFPS()) + "\n"
				+ "X: " + std::to_string(player->position.x) + " Y: " + std::to_string(player->position.y) + "\n"
				+ "Cx: " + std::to_string(player->chunkPosition.x) + " Cy: " + std::to_string(player->chunkPosition.y) + "\n"
				+ "ChunkBuffer size: " + std::to_string(Globals::chunkBufferSize) + "\n"
				+ "ConsoleString size: " + std::to_string(console->input.getSize()));

	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

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
	//Create Rectangles for hotbar, item and selected indicator
	sf::RectangleShape hotbarRectangle(sf::Vector2f(64, 64));
	sf::RectangleShape itemRectangle(sf::Vector2f(48, 48));
	sf::RectangleShape selectedRectangle(sf::Vector2f(64, 64));

	//Create sf::Text for amount indicator
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	//Configuring hotbarRectangle
	hotbarRectangle.setFillColor(sf::Color(0, 0, 0, 128));
	hotbarRectangle.setOutlineThickness(1);
	hotbarRectangle.setOutlineColor(sf::Color::Black);

	//If name == PizzaHannes, golden selctedRect
	if (player->name == "PizzaHannes") {
		selectedRectangle.setOutlineColor(sf::Color(218, 165, 32));
	}
	else {
		selectedRectangle.setOutlineColor(sf::Color::Red);
	}
	
	selectedRectangle.setOutlineThickness(2);
	selectedRectangle.setFillColor(sf::Color::Transparent);

	//Draw Hotbar
	for (int i = 0; i < 8; i++) {
		hotbarRectangle.setPosition(window->getSize().x / 2 -320 + (i*74), window->getSize().y - 74);
		window->draw(hotbarRectangle);

		//Draw selected indicator
		if (player->selectedItem == i) {
			selectedRectangle.setPosition(window->getSize().x / 2 - 320 + (i * 74), window->getSize().y - 74);
			window->draw(selectedRectangle);
		}

		//Draw item
		if ((int)player->inventory[i][0] != 0) {
			itemRectangle.setFillColor(getTileColor(player->inventory[i][0]));
			itemRectangle.setPosition(window->getSize().x / 2 - 320 + (i * 74) + 8, window->getSize().y - 74 + 8);
			window->draw(itemRectangle);

			text.setString(std::to_string(player->inventory[i][1]));
			text.setPosition(window->getSize().x / 2 - 320 + (i * 74) + 8, window->getSize().y - 74 + 8);
			window->draw(text);
		}
	}

	
}

void Renderer::renderInventory(Player* player)
{
	//Create Rectangles
	sf::RectangleShape inventoryRectangle(sf::Vector2f(589, 289));
	sf::RectangleShape frameRectangle(sf::Vector2f(64, 64));
	sf::RectangleShape itemRectangle(sf::Vector2f(48, 48));

	//Create sf::Text for amount indicator
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	//Create anchor point
	sf::Vector2f anchor = sf::Vector2f( window->getSize().x / 2 - (589 / 2), window->getSize().y / 2 - (289 / 2));

	//Set inventoryBackground
	inventoryRectangle.setPosition(anchor);
	inventoryRectangle.setFillColor(sf::Color(64, 64, 64));

	//Set frame
	frameRectangle.setFillColor(sf::Color(32, 32, 32));

	window->draw(inventoryRectangle);

	//Set frameRectangle
	for (int y = 0; y < (player->inventorySlotSize - 8) / 8; y++) {
		for (int x = 0; x < (player->inventorySlotSize - 8) / 4; x++) {
			frameRectangle.setPosition(sf::Vector2f(anchor.x + x * 75, anchor.y + y * 75));
			window->draw(frameRectangle);

			if (player->inventory[y +1 * 8 + x][1] > 0) {
				itemRectangle.setFillColor(getTileColor(player->inventory[y +1 * 8 + x][0]));
				itemRectangle.setPosition(sf::Vector2f(anchor.x + x * 75 + 8, anchor.y + y * 75 + 8));
				window->draw(itemRectangle);

				text.setString(std::to_string(player->inventory[y +1 * 8 + x][1]));
				text.setPosition(sf::Vector2f(anchor.x + x * 75 + 8, anchor.y + y * 75 + 8));
				window->draw(text);
			}
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
