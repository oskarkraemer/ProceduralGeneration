#include "ChunkLoader.h"

void ChunkLoader::loadChunksToBuffer(Player* player, bool existsInBufferCheck) {
    int cntr = 0;

    std::cout << std::endl << "[NEW CHUNK UPDATE]" << std::endl;


    for (int x = player->chunkPosition.x - load_radius; x <= player->chunkPosition.x + load_radius; x++) {
        for (int y = player->chunkPosition.y - load_radius; y <= player->chunkPosition.y + load_radius; y++) {

            std::stringstream ss;
            ss << "./world/" << x << "_" << y << ".chunk";

            std::ifstream file;
            file.open(ss.str());



            if (file) {
                    
                world->chunkBuffer[cntr] = loadChunkFromFile(x, y);
                renderer->loadChunkVertices(&world->chunkBuffer[cntr]);
            }
            else {

                world->chunkBuffer[cntr].x = x; world->chunkBuffer[cntr].y = y;
                terrainGenerator->generateChunk(&world->chunkBuffer[cntr], 0);
                renderer->loadChunkVertices(&world->chunkBuffer[cntr]);

                saveChunkToFile(&world->chunkBuffer[cntr]);
            }


            std::cout << "|| X: " << x << " Y: " << y << std::endl;

            cntr++;
        }
    }
}

void ChunkLoader::saveChunkToFile(Chunk* chunk) {
    std::ofstream file;
    std::stringstream ss;

    ss << "./world/" << chunk->x << "_" << chunk->y << ".chunk";

    file.open(ss.str());

    file << *chunk;

    file.close();
}

Chunk ChunkLoader::loadChunkFromFile(int x, int y) {
    std::ifstream file;
    std::stringstream ss;
    Chunk chunk;

    std::cout << "Load File: " << x << " " << y << std::endl;

    ss << "./world/" << x << "_" << y << ".chunk";

    file.open(ss.str());

    if (!file.good()) {
        std::cout << "File opening failed!" << std::endl;
    }
    else {

        chunk.vertices = sf::VertexArray();
        file >> chunk;
    }

    file.close();

    return chunk;

}