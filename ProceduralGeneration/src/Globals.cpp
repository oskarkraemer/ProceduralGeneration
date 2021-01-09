#include "Globals.h"

uint8_t chunk_size = 32;
uint8_t tile_size = 32;
uint8_t load_radius = 1;
int chunkBufferSize = 4 * load_radius + 4 * (load_radius * load_radius) + 1;