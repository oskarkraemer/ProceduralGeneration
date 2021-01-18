#include "Console.h"

int Console::processInput(Player* player, sf::RenderWindow* window) {
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

	//Print ArgsVector
	for (int i = 0; i < args.size(); i++) {
		std::cout << args[i] << std::endl;
	}

	//Interpret args

	//Clear inventory
	if (args[0] == "clear") {
		player->clearInventory();
	}

	//setFullscreen
	else if (args[0] == "setFullscreen") {
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
		player->savePlayer();
		window->close();
	}
	

	return 0;
}

void Console::clear() {
	input.clear();
}