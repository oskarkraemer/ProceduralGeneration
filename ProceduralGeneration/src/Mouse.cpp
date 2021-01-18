#include "Mouse.h"

void Mouse::updateHighlighting(sf::RenderWindow* window) {
    
    highlightRectangle.setSize(sf::Vector2f(tile_size, tile_size));
    highlightRectangle.setFillColor(sf::Color::Transparent);
    highlightRectangle.setOutlineColor(sf::Color(186, 186, 186));
    highlightRectangle.setOutlineThickness(1);

    pixelPos = sf::Mouse::getPosition();
    worldPos = window->mapPixelToCoords(pixelPos);

    
    tilePos.x = floor(worldPos.x / tile_size);
    tilePos.y = floor(worldPos.y / tile_size);

    if (!isFullscreen) {
        tilePos.x -= 5;
        tilePos.y -= 3;
    }

    highlightRectangle.setPosition(sf::Vector2f(tilePos.x * tile_size, tilePos.y * tile_size));

    window->draw(highlightRectangle);
    
}

void Mouse::updateBlockBreak() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        chunkPos.x = floor(tilePos.x / (float)chunk_size);
        chunkPos.y = floor(tilePos.y / (float)chunk_size);

        for (int i = 0; i < chunkBufferSize; i++) {
            if (world->chunkBuffer[i].x == chunkPos.x && world->chunkBuffer[i].y == chunkPos.y) {
                for (int y = 0; y < chunk_size; y++) {
                    for (int x = 0; x < chunk_size; x++) {
                        if (y + chunkPos.y * chunk_size == tilePos.y && x + chunkPos.x * chunk_size == tilePos.x) {

                            if (world->chunkBuffer[i].tileTypes[y * chunk_size + x] != 0) {
                                player->addToInventory(world->chunkBuffer[i].tileTypes[y * chunk_size + x], 1);
                                world->chunkBuffer[i].tileTypes[y * chunk_size + x] = 0;

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
            chunkPos.x = floor(tilePos.x / (float)chunk_size);
            chunkPos.y = floor(tilePos.y / (float)chunk_size);

            for (int i = 0; i < chunkBufferSize; i++) {
                if (world->chunkBuffer[i].x == chunkPos.x && world->chunkBuffer[i].y == chunkPos.y) {
                    for (int y = 0; y < chunk_size; y++) {
                        for (int x = 0; x < chunk_size; x++) {
                            if (y + chunkPos.y * chunk_size == tilePos.y && x + chunkPos.x * chunk_size == tilePos.x) {

                                if (world->chunkBuffer[i].tileTypes[y * chunk_size + x] == 0) {

                                    world->chunkBuffer[i].tileTypes[y * chunk_size + x] = player->inventory[player->selectedItem][0];
                                    player->removeFromInventory(player->inventory[player->selectedItem][0], 1);

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