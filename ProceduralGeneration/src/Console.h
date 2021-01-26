#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include "logging/loguru.hpp"

#include "Player.h"
#include "World.h"

namespace Types {
	enum Type {
		NUMERICAL, STRING, BOOL
	};
}

class Console
{
public:
	sf::String input;

	//Procceses Input and returns 1 when unsucsessfull
	int processInput(Player* player, sf::RenderWindow* window, World* world);

	bool isInteger(const std::string& s);
	bool checkTemplate(const char* command, int argument_count, std::vector<std::string>* args, std::vector<Types::Type>* types = &std::vector<Types::Type>());

	void clear();

	
};

