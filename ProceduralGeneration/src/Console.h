#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#include "Player.h"
#include "World.h"

class Console
{
public:
	sf::String input;

	//Procceses Input and returns 1 when unsucsessfull
	int processInput(Player* player, sf::RenderWindow* window, World* world);
	void clear();

	
};

