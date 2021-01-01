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

		os << s.tileTypes <<'\n';
		os << s.x << '\n';
		os << s.y;
		return os;
	}

	// Extraction operator
	friend std::istream& operator>>(std::istream& is, Chunk& s)
	{
		is >> s.tileTypes;
		is >> s.x;
		is >> s.y;

		return is;
	}
};

