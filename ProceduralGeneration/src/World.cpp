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
	
	//Set world seed
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<unsigned int> distr(0, std::numeric_limits<unsigned int>::max());
	seed = distr(gen);

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

	//Save world seed
	file << seed << '\n';

	file.close();
}

void World::loadWorld() {
	std::ifstream file;
	std::stringstream ss;

	std::string line;

	ss << Globals::worldsFolderPath << name << "/" << "meta.data";

	file.open(ss.str());

	if (!file.good()) {
		LOG_F(WARNING, "World save file could not be loaded!");
	}
	else {
		//Load world name
		file >> name;

		//Load world seed
		file >> seed;

		loaded = true;
	}

	emptyChunkBuffer();

	file.close();
}