#include "Console.h"

int Console::processInput(Player* player, sf::RenderWindow* window, World* world) {
	//SPLIT ARGUMENTS
	
	std::string string = input.toAnsiString();
	std::istringstream iss(string);

	std::vector<std::string> args;

	do {
		std::string sub;
		iss >> sub;

		if (!sub.empty()) {
			args.push_back(sub);
		}
	} while (iss);

	std::cout << "[Command]: " << string << "\n";

	//Interpret args

	//Clear inventory
	if (args[0] == "clear") {
		player->clearInventory();
	}

	//setFullscreen
	else if (args[0] == "setFullscreen" && args.size()==2) {
		if (args[1] == "true") {
			isFullscreen = true;
			window->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProceduralGeneration", sf::Style::Fullscreen);
		}
		else if (args[1] == "false") {
			isFullscreen = false;
			window->create(sf::VideoMode(1920, 1080), "ProceduralGeneration");
		}
	}

	//Exits and saves Game
	else if (args[0] == "exit") {
		player->savePlayer(world);
		window->close();
	}

	//create world with name
	else if (args[0] == "createWorld" && args.size() == 2) {
		if (args[1] != "") {
			world->name = args[1];
			world->createWorld();
			world->loadWorld();
		}
	}

	//load world with name
	else if (args[0] == "loadWorld" && args.size() == 2) {
		if (args[1] != "") {
			world->name = args[1];
			world->loadWorld();
			player->loadPlayer(world);

			player->setPosition(player->position);
			player->oldChunkPosition.x++; // create difference between old and new position in order to trigger chunk generation
		}
	}
	
	else if (args[0] == "give" && args.size() == 3) {
		if (args[1] != "" && args[2] != "") {
			player->addToInventory(std::stoi(args[1]), std::stoi(args[2]));
		}
	}

	return 0;
}

void Console::clear() {
	input.clear();
}