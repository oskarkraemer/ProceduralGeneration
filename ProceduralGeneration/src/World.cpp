#include "World.h"

int World::createWorld() {
	int status = 0;

	//Create Directories
	std::string path = Globals::worldsFolderPath;
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();
	status = CreateDirectory(sw, NULL);

	path = Globals::worldsFolderPath + name + "\\";
	stemp = std::wstring(path.begin(), path.end());
	sw = stemp.c_str();
	CreateDirectory(sw, NULL);

	path = Globals::worldsFolderPath + name + "\\players\\";
	stemp = std::wstring(path.begin(), path.end());
	sw = stemp.c_str();
	CreateDirectory(sw, NULL);

	path = Globals::worldsFolderPath + name + "\\chunks\\";
	stemp = std::wstring(path.begin(), path.end());
	sw = stemp.c_str();
	CreateDirectory(sw, NULL);

	//Save World class
	saveWorld();
	return status;

}

void World::emptyChunkBuffer() {
	chunkBuffer.resize(Globals::chunkBufferSize);

	for (int i = 0; i < Globals::chunkBufferSize; i++) {
		chunkBuffer[i] = Chunk();
	}
}

void World::saveWorld() {
	std::ofstream file;
	std::stringstream ss;

	ss << Globals::worldsFolderPath << name << "/" << "meta.data";

	file.open(ss.str());

	//Save world name
	file << name << '\n';

	file.close();
}

void World::loadWorld() {
	std::ifstream file;
	std::stringstream ss;

	std::string line;

	ss << Globals::worldsFolderPath << name << "/" << "meta.data";

	file.open(ss.str());

	if (!file.good()) {
		std::cout << "File opening failed!" << "\n";
	}
	else {
		//Load world name
		file >> name;

		loaded = true;
	}

	emptyChunkBuffer();

	file.close();
}