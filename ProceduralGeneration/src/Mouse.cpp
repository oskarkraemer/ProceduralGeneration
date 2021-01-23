#include "Mouse.h"

void Mouse::updateHighlighting(sf::RenderWindow* window) {
    
    highlightRectangle.setSize(sf::Vector2f(Globals::tile_size, Globals::tile_size));
    highlightRectangle.setFillColor(sf::Color::Transparent);
    highlightRectangle.setOutlineColor(sf::Color(186, 186, 186));
    highlightRectangle.setOutlineThickness(1);

    pixelPos = sf::Mouse::getPosition();
    worldPos = window->mapPixelToCoords(pixelPos);

    
    tilePos.x = floor(worldPos.x / Globals::tile_size);
    tilePos.y = floor(worldPos.y / Globals::tile_size);

    if (!Globals::isFullscreen) {
        tilePos.x -= 5;
        tilePos.y -= 3;
    }

    highlightRectangle.setPosition(sf::Vector2f(tilePos.x * Globals::tile_size, tilePos.y * Globals::tile_size));

    window->draw(highlightRectangle);
    
}

void Mouse::updateBlockBreak() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        chunkPos.x = floor(tilePos.x / (float)Globals::chunk_size);
        chunkPos.y = floor(tilePos.y / (float)Globals::chunk_size);

        for (int i = 0; i < Globals::chunkBufferSize; i++) {
            if (world->chunkBuffer[i].x == chunkPos.x && world->chunkBuffer[i].y == chunkPos.y) {
                for (int y = 0; y < Globals::chunk_size; y++) {
                    for (int x = 0; x < Globals::chunk_size; x++) {
                        if (y + chunkPos.y * Globals::chunk_size == tilePos.y && x + chunkPos.x * Globals::chunk_size == tilePos.x) {

                            if (world->chunkBuffer[i].tileTypes[y * Globals::chunk_size + x] != 0) {
                                player->addToInventory(world->chunkBuffer[i].tileTypes[y * Globals::chunk_size + x], 1);
                                world->chunkBuffer[i].tileTypes[y * Globals::chunk_size + x] = 0;

                                renderer->loadChunkVertices(&world->chunkBuffer[i]);

                                chunkLoader->saveChunkToFile(&world->chunkBuffer[i]);
                                goto end;
                            }
                        }
                    }
                }
            }
        }

    }
end:;

}

void Mouse::updateBlockPlace() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (player->inventory[player->selectedItem][1] > 0) {
            chunkPos.x = floor(tilePos.x / (float)Globals::chunk_size);
            chunkPos.y = floor(tilePos.y / (float)Globals::chunk_size);

            for (int i = 0; i < Globals::chunkBufferSize; i++) {
                if (world->chunkBuffer[i].x == chunkPos.x && world->chunkBuffer[i].y == chunkPos.y) {
                    for (int y = 0; y < Globals::chunk_size; y++) {
                        for (int x = 0; x < Globals::chunk_size; x++) {
                            if (y + chunkPos.y * Globals::chunk_size == tilePos.y && x + chunkPos.x * Globals::chunk_size == tilePos.x) {

                                if (world->chunkBuffer[i].tileTypes[y * Globals::chunk_size + x] == 0) {

                                    world->chunkBuffer[i].tileTypes[y * Globals::chunk_size + x] = player->inventory[player->selectedItem][0];
                                    player->removeFromInventoryAtIndex(player->selectedItem, 1);

                                    renderer->loadChunkVertices(&world->chunkBuffer[i]);

                                    chunkLoader->saveChunkToFile(&world->chunkBuffer[i]);
                                    goto end;
                                }
                            }
                        }
                    }
                }
            }
        }

    }
end:;

}