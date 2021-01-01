#include "ChunkLoader.h"

void ChunkLoader::loadChunksToBuffer(Player* player, bool existsInBufferCheck) {
    int cntr = 0;
    bool loaded = false;



    for (int x = player->chunkPosition.x - load_radius; x <= player->chunkPosition.x + load_radius; x++) {
        for (int y = player->chunkPosition.y - load_radius; y <= player->chunkPosition.y + load_radius; y++) {

            if (existsInBufferCheck) {
                for (int i = 0; i < chunkBufferSize; i++) {
                    if (world->chunkBuffer[i].x == x && world->chunkBuffer[i].y == y) {
                        loaded = true;
                    }
                }
            }

            if (!loaded) {
                std::ifstream infile(std::to_string(x) + "_" + std::to_string(y) + ".chunk");

                if (infile.good()) {

                    world->chunkBuffer[cntr] = loadChunkFromFile(x, y);
                }
                else {

                    world->chunkBuffer[cntr].x = x; world->chunkBuffer[cntr].y = y;
                    terrainGenerator->generateChunk(&world->chunkBuffer[cntr], 0);
                    renderer->loadChunkVertices(&world->chunkBuffer[cntr]);

                    saveChunkToFile(&world->chunkBuffer[cntr]);
                }
            }

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

    ss << "./world/" << x << "_" << y << ".chunk";

    file.open(ss.str());


    file >> chunk;

    file.close();

    return chunk;

}