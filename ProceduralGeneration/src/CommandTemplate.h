#pragma once
#include <string>
#include <vector>


namespace Types {
	enum Type {
		NUMERICAL, STRING, BOOL
	};
}

	struct CommandTemplate
	{

		std::string command = "";

		int argument_count = 0;
		std::vector<Types::Type> types;


		CommandTemplate(std::string Ccommand, int Cargument_count, std::vector<Types::Type> Ctypes = std::vector<Types::Type>() ) {
			command = Ccommand;
			argument_count = Cargument_count;
			types = Ctypes;
		}
	};
