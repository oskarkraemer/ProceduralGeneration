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
	if ( checkTemplate( &CommandTemplate("clear", 0) , &args) ) {
		player->clearInventory();
	}

	//setFullscreen
	else if (checkTemplate(&CommandTemplate("setFullscreen", 1, std::vector<Types::Type> {Types::BOOL}), &args)) {
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
	else if (checkTemplate(&CommandTemplate("exit", 0), &args)) {
		player->savePlayer(world);
		window->close();
	}

	//create world with name
	else if (checkTemplate(&CommandTemplate("createWorld", 1, std::vector<Types::Type> {Types::STRING}), &args)) {
		world->name = args[1];
		world->createWorld();
		world->loadWorld();
	}

	//load world with name
	else if (checkTemplate(&CommandTemplate("loadWorld", 1, std::vector<Types::Type> {Types::STRING}), &args)) {
		world->name = args[1];
		world->loadWorld();
		player->loadPlayer(world);

		player->setPosition(player->position);

	}
	
	//give items to player
	else if (checkTemplate(&CommandTemplate("give", 2, std::vector<Types::Type> {Types::NUMERICAL, Types::NUMERICAL}), &args)) {
		player->addToInventory(std::stoi(args[1]), std::stoi(args[2]));
	}

	//teleport player to coordinates
	else if (checkTemplate(&CommandTemplate("tp", 2, std::vector<Types::Type> {Types::NUMERICAL, Types::NUMERICAL}), &args)) {
		player->setPosition(sf::Vector2f(std::stoi(args[1]), std::stoi(args[2])));
	}

	return 0;
}

bool Console::checkTemplate(CommandTemplate* commandTemplate, std::vector<std::string>* args) {
	//Check if Vector is the appropriate size
	if (args->size() == commandTemplate->argument_count + 1) {

		//Check if there are any empty emelements in Vector
		for (int i = 0; i < commandTemplate->argument_count + 1; i++) {
			if (args->at(i).empty()) { goto failed; }
		}

		//Check if element 1 in vector is command
		if (args->at(0) == commandTemplate->command) {

			//Check if the remaining arguments have the right type
			for (int i = 0; i < commandTemplate->argument_count; i++) {

				//Check if type is BOOL
				if (commandTemplate->types[i] == Types::BOOL) {
					if (args->at(i + 1) != "true" && args->at(i + 1) != "false") {
						goto failed;
					}
				}

				//Check if type is NUMERICAL
				if (commandTemplate->types[i] == Types::NUMERICAL) {
					if(args->at(i + 1).find_first_not_of("0123456789") != std::string::npos) {
						goto failed;
					}
				}


			}

			return true;
		}
	}

	failed:
	return false;
}

void Console::clear() {
	input.clear();
}