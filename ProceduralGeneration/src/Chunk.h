#pragma once
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class Chunk
{

public:

	uint8_t tileTypes[256]; // chunkSize * chunkSize

	int x = 0, y = 0;

	sf::VertexArray vertices;

	// Insertion operator
	friend std::ostream& operator<<(std::ostream& os, const Chunk& s)
	{
		for (int i = 0; i < 256; i++) {
			os << s.tileTypes[i];
		}
		
		os << s.x << '\n';
		os << s.y;
		return os;
	}

	// Extraction operator
	friend std::istream& operator>>(std::istream& is, Chunk& s)
	{
		for (int i = 0; i < 256; i++) {
			is >> s.tileTypes[i];
		}


		is >> s.x >> s.y;

		return is;
	}
};

