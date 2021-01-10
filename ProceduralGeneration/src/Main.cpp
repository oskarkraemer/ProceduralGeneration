#include "PerlinNoise.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <thread>

#include "TerrainGeneration.h"
#include "world.h"
#include "Renderer.h"
#include "Globals.h"
#include "Player.h"
#include "ChunkLoader.h"

#include "FPS.h"


int main() {
    //TO:DO
    //- fix reapting tile pattern every 256 tiles in chunk

    World* world = new World;
    Player player;
    player.setPosition(sf::Vector2f(0,0));

    FPS fps;
    TerrainGeneration tr;
    //sf::RenderWindow window(sf::VideoMode(1280, 720), "ProcTerr");
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ProcTerr");
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProcTerr", sf::Style::Fullscreen); //fullscreen

    Renderer renderer(&window);
    ChunkLoader chunkLoader(world, &renderer, &tr);


    world->chunkBuffer.resize(chunkBufferSize);


    player.oldChunkPosition.x++; // create difference between old and new position in order to trigger chunk generation

    bool toggleDebugInformation = false;
    
    for (int i = 0; i < chunkBufferSize; i++) {
        world->chunkBuffer[i] = Chunk();
    }


    uint16_t stackSize = sizeof(world) + sizeof(fps) + sizeof(tr) + sizeof(renderer);
    uint16_t heapSize = chunkBufferSize * sizeof(Chunk);

    std::cout << "StackMemory used: " << stackSize << " | " << (float)stackSize / 1024 << "KB" << std::endl;
    std::cout << "HeapMemory used: " << heapSize <<" | " << (float)heapSize /1024 << "KB"<< std::endl;
    
    sf::Clock clock;
    int movSpeed = 800;

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                
                //toggle debugInformation
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::F3) {
                        toggleDebugInformation = !toggleDebugInformation;
                    }
            }
            
        }
        
        sf::Time elapsedTime = clock.restart();
        float tempSpeed = elapsedTime.asSeconds() * movSpeed;

        //MOVEMINT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            //std::cout << "Pressed W" << player.position.y << " "<<player.chunkPosition.y<< std::endl;
            player.setPosition(sf::Vector2f(player.position.x, player.position.y - tempSpeed));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            //std::cout << "Pressed D" << player.position.x << " " << player.chunkPosition.x << std::endl;
            player.setPosition(sf::Vector2f(player.position.x+ tempSpeed, player.position.y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            //std::cout << "Pressed A" << player.position.x << " " << player.chunkPosition.x << std::endl;
            player.setPosition(sf::Vector2f(player.position.x - tempSpeed, player.position.y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            //std::cout << "Pressed S" << player.position.y << " " << player.chunkPosition.y << std::endl;
            player.setPosition(sf::Vector2f(player.position.x, player.position.y + tempSpeed));
        }


        

        /*
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition();
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            std::cout << worldPos.x/32 << " "<< worldPos.y/32 << std::endl;
            for (int i = 0; i < chunkBufferSize; i++) {
                for (int y = 0; y < chunk_size * chunk_size; y++) {
                    if (world->chunkBuffer[i].x == floor(worldPos.x / 32) && world->chunkBuffer[i].y == floor(worldPos.x / 32)) {
                        world->chunkBuffer[i].tileTypes[0] = 0;
                        renderer.loadChunkVertices(&world->chunkBuffer[i]);
                    }
                }
            }
        }*/

        window.clear(sf::Color::Black);
        window.setView(player.view);


        if (player.chunkPosition.x != player.oldChunkPosition.x || player.chunkPosition.y != player.oldChunkPosition.y) {
           
            //chunkLoader.loadChunksToBuffer(&player, true);

            std::thread t1(&ChunkLoader::loadChunksToBuffer, &chunkLoader, &player, true);
            t1.join();

            player.oldChunkPosition.x = player.chunkPosition.x;
            player.oldChunkPosition.y = player.chunkPosition.y;
        }

        renderer.renderChunkBuffer(world);
        

        renderer.renderChunkBorders(world);
        renderer.renderPlayer(&player);

        //Render GUI
        window.setView(window.getDefaultView());
        if (toggleDebugInformation) {
            renderer.renderDebugInformation(&player, &fps);
        }
        
        fps.update();
        
        window.display();
    }
}