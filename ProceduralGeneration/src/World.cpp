#include "World.h"

int World::createWorld() {
	int status = 0;

	//Create Directories
	std::string path = ".\\" + name + "\\";
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();
	status = CreateDirectory(sw, NULL);

	path = ".\\" + name + "\\players\\";
	stemp = std::wstring(path.begin(), path.end());
	sw = stemp.c_str();
	CreateDirectory(sw, NULL);

	path = ".\\" + name + "\\chunks\\";
	stemp = std::wstring(path.begin(), path.end());
	sw = stemp.c_str();
	CreateDirectory(sw, NULL);

	//Save World class
	saveWorld();
	return status;

}

void World::saveWorld() {
	std::ofstream file;
	std::stringstream ss;

	ss << "./"<< name << "/" << "meta.data";

	file.open(ss.str());

	//Save world name
	file << name << '\n';

	file.close();
}

void World::loadWorld() {
	std::ifstream file;
	std::stringstream ss;

	std::string line;

	ss << "./" << name << "/" << "meta.data";

	file.open(ss.str());

	if (!file.good()) {
		std::cout << "File opening failed!" << "\n";
	}
	else {
		//Load world name
		file >> name;

		loaded = true;
	}

	file.close();
}