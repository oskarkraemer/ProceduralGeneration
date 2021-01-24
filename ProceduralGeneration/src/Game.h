#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <thread>
#include "logging/loguru.hpp"

#include "TerrainGeneration.h"
#include "world.h"
#include "Renderer.h"
#include "Globals.h"
#include "Player.h"
#include "ChunkLoader.h"
#include "Mouse.h"
#include "Console.h"

#include "FPS.h"

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::Clock clock;

	//Game Classes
	World* world;
	Player* player;
	FPS fps;
	TerrainGeneration tr;
	Renderer* renderer;
	ChunkLoader* chunkLoader;
	Mouse* mouse;
	Console console;

	//Others
	bool toggleDebugInformation = false;
	bool toggleConsole = false;
	

	//Private funtions
	void initLogging();
	void initVariables();
	void initWindow();
	void initGameObjects();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void update();
	void pollEvents();
	void render();
};
