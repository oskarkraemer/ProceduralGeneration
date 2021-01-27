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

	
	

	LOG_F(INFO, "[Command]: %s", string.c_str());

	//Interpret args

	//Clear inventory
	if ( checkTemplate("clear", 0, &args) ) {
		player->clearInventory();
	}

	//setFullscreen
	else if (checkTemplate("setFullscreen", 1, &args, &std::vector<Types::Type> {Types::BOOL})) {
		if (args[1] == "true") {
			Globals::isFullscreen = true;
			window->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProceduralGeneration", sf::Style::Fullscreen);
		}
		else if (args[1] == "false") {
			Globals::isFullscreen = false;
			window->create(sf::VideoMode(1920, 1080), "ProceduralGeneration");
		}
	}

	//Exits and saves Game
	else if (checkTemplate("exit", 0, &args)) {
		player->savePlayer(world);
		window->close();
	}

	//create world with name
	else if (checkTemplate("createWorld", 1, &args, &std::vector<Types::Type> {Types::STRING})) {
		player->savePlayer(world);

		world->name = args[1];
		world->createWorld();
		world->loadWorld();
		player->loadPlayer(world);

	}

	//load world with name
	else if (checkTemplate("loadWorld", 1, &args, &std::vector<Types::Type> {Types::STRING})) {
		player->savePlayer(world);

		world->name = args[1];
		world->loadWorld();
		player->loadPlayer(world);

	}
	
	//give items to player
	else if (checkTemplate("give", 2, &args, &std::vector<Types::Type> {Types::NUMERICAL, Types::NUMERICAL})) {
		player->addToInventory(std::stoi(args[1]), std::stoi(args[2]));
	}

	//teleport player to coordinates
	else if (checkTemplate("tp", 2, &args, &std::vector<Types::Type> {Types::NUMERICAL, Types::NUMERICAL})) {
		int maxPixelSize = Globals::worldSize * Globals::chunk_size * Globals::tile_size;

		try {
			if (std::stoi(args[1]) < maxPixelSize && std::stoi(args[1]) > -maxPixelSize) {
				if (std::stoi(args[2]) < maxPixelSize && std::stoi(args[2]) > -maxPixelSize) {
					player->setPosition(sf::Vector2f(std::stoi(args[1]), std::stoi(args[2])));
				}
			}	
		}
		catch (const std::out_of_range& e) {

		}

	}

	//list all worlds in worlds folder
	else if (checkTemplate("listWorlds", 0, &args)) {

	}

	return 0;
}

bool Console::isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char* p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

bool Console::checkTemplate(const char* command, int argument_count, std::vector<std::string>* args, std::vector<Types::Type>* types) {
	//Check if Vector is the appropriate size
	if (args->size() == argument_count + 1) {

		//Check if there are any empty emelements in Vector
		for (int i = 0; i < argument_count + 1; i++) {
			if (args->at(i).empty()) { goto failed; }
		}

		//Check if element 1 in vector is command
		if (args->at(0) == command) {

			//Check if the remaining arguments have the right type
			for (int i = 0; i < argument_count; i++) {

				//Check if type is BOOL
				if (types->at(i) == Types::BOOL) {
					if (args->at(i + 1) != "true" && args->at(i + 1) != "false") {
						goto failed;
					}
				}

				//Check if type is NUMERICAL
				if (types->at(i) == Types::NUMERICAL) {
					if (!isInteger(args->at(i+1))) {
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