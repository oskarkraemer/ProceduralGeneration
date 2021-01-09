#pragma once
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"

class Chunk
{

public:

	uint8_t tileTypes[1024]; // chunkSize * chunkSize

	int x = 0, y = 0;

	sf::VertexArray vertices;

	// Insertion operator
	friend std::ostream& operator<<(std::ostream& os, const Chunk& s)
	{
		for (int i = 0; i < chunk_size * chunk_size; i++) {
			os << s.tileTypes[i];
		}
		
		os << '\n';
		os << s.x << '\n';
		os << s.y;
		return os;
	}

	// Extraction operator
	friend std::istream& operator>>(std::istream& is, Chunk& s)
	{
		for (int i = 0; i < chunk_size*chunk_size; i++) {
			is >> s.tileTypes[i];
		}

		is >> s.x >> s.y;

		return is;
	}
};

