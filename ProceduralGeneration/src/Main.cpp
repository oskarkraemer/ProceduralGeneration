#include "PerlinNoise.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "TerrainGeneration.h"
#include "world.h"
#include "Renderer.h"
#include "Globals.h"
#include "Player.h"
#include "ChunkLoader.h"

#include "FPS.h"


int main() {
    //TO:DO
    //- fix lag at chunk transitions (maybe reduce file loads by only using one file for chunks)

    World* world = new World;
    Player player;
    player.setPosition(sf::Vector2f(300,300));

    FPS fps;
    TerrainGeneration tr;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ProcTerr");
    //sf::RenderWindow window(sf::VideoMode(1920, 1080), "ProcTerr");
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProcTerr", sf::Style::Fullscreen); //fullscreen

    Renderer renderer(&window);
    ChunkLoader chunkLoader(world, &renderer, &tr);

    Chunk chunk;
    chunk.x = 55;
    chunk.y = 32;
    tr.generateChunk(&chunk, 4);

    chunkLoader.saveChunkToFile(&chunk);

    chunkLoader.loadChunkFromFile(55, 32);

    world->chunkBuffer.reserve(chunkBufferSize);


    player.oldChunkPosition.x++; // create difference between old and new position in order to trigger chunk generation
    


    uint16_t stackSize = sizeof(world) + sizeof(fps) + sizeof(tr) + sizeof(renderer);
    uint16_t heapSize = chunkBufferSize * sizeof(Chunk);

    std::cout << "StackMemory used: " << stackSize << " | " << (float)stackSize / 1024 << "KB" << std::endl;
    std::cout << "HeapMemory used: " << heapSize <<" | " << (float)heapSize /1024 << "KB"<< std::endl;
    
    sf::Clock clock;
    int movSpeed = 1500;

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Time elapsedTime = clock.restart();
        float tempSpeed = elapsedTime.asSeconds() * movSpeed;

        //MOVEMINT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            std::cout << "Pressed W" << player.position.y << " "<<player.chunkPosition.y<< std::endl;
            player.setPosition(sf::Vector2f(player.position.x, player.position.y - tempSpeed));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            std::cout << "Pressed D" << player.position.x << " " << player.chunkPosition.x << std::endl;
            player.setPosition(sf::Vector2f(player.position.x+ tempSpeed, player.position.y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            std::cout << "Pressed A" << player.position.x << " " << player.chunkPosition.x << std::endl;
            player.setPosition(sf::Vector2f(player.position.x - tempSpeed, player.position.y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            std::cout << "Pressed S" << player.position.y << " " << player.chunkPosition.y << std::endl;
            player.setPosition(sf::Vector2f(player.position.x, player.position.y + tempSpeed));
        }

        window.clear(sf::Color::Black);


        if (player.chunkPosition.x != player.oldChunkPosition.x || player.chunkPosition.y != player.oldChunkPosition.y) {
            
            chunkLoader.loadChunksToBuffer(&player);

            player.oldChunkPosition.x = player.chunkPosition.x;
            player.oldChunkPosition.y = player.chunkPosition.y;
        }

        renderer.renderChunkBuffer(world);
        

        renderer.renderChunkBorders();
        renderer.renderPlayer(&player);
        renderer.renderFPS(&fps);
        
        fps.update();
        
        window.display();
    }
}