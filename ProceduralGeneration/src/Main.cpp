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
#include "Mouse.h"
#include "Console.h"

#include "FPS.h"


int main() {
    //TO:DO
    //- fix perlin noise between chunks, it cuts off at the chunk borders
    //- fix mouse offsetting when window dragged
    //- add console

    World* world = new World;

    //Initialize Player
    Player player("PizzaHannes");
    player.loadPlayer();
    
    player.setPosition(player.position);
    

    CreateDirectory(L".\\world\\", NULL);
    CreateDirectory(L".\\world\\players\\", NULL);
    CreateDirectory(L".\\world\\chunks\\", NULL);

    

    FPS fps;
    TerrainGeneration tr;
    sf::RenderWindow window;
    

    if (isFullscreen) {
        window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProceduralGeneration", sf::Style::Fullscreen);

    }
    else {
        window.create(sf::VideoMode(1920, 1080), "ProceduralGeneration");
    }
    

    window.setFramerateLimit(144);

    Renderer renderer(&window);
    if (!renderer.font.loadFromFile("./res/Roboto-Regular.ttf")) {
        return 1;
    }

    ChunkLoader chunkLoader(world, &renderer, &tr);

    Mouse mouse(world, &renderer, &chunkLoader, &player);

    Console console;
    

    world->chunkBuffer.resize(chunkBufferSize);


    player.oldChunkPosition.x++; // create difference between old and new position in order to trigger chunk generation

    bool toggleDebugInformation = false;
    bool toggleConsole = false;
    
    for (int i = 0; i < chunkBufferSize; i++) {
        world->chunkBuffer[i] = Chunk();
    }


    //
    // Display used Memory
    //

    uint16_t stackSize = sizeof(world) + sizeof(fps) + sizeof(tr) + sizeof(renderer)+ sizeof(player) + sizeof(chunkLoader) + sizeof(mouse) + sizeof(window);
    uint16_t heapSize = chunkBufferSize * sizeof(Chunk);

    std::cout << "StackMemory used: " << stackSize << " | " << (float)stackSize / 1024 << "KB" << std::endl;
    std::cout << "HeapMemory used: " << heapSize <<" | " << (float)heapSize /1024 << "KB"<< std::endl;

    //
    // [-----------------]
    //
    
    sf::Clock clock;
    int movSpeed = 800;

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    player.savePlayer();
                    window.close();

                case sf::Event::TextEntered:
                    if (toggleConsole) {
                        if (event.text.unicode == '\b') {
                            if (console.input.getSize() > 0) {
                                console.input.erase(console.input.getSize() - 1, 1);
                            }
                        }
                        else if (event.text.unicode < 128 && event.text.unicode!=27) {
                            console.input += event.text.unicode;
                        }
                        
                    }


                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::F3) {
                        toggleDebugInformation = !toggleDebugInformation;
                    }

                    else if (event.key.code == sf::Keyboard::T) {
                        toggleConsole = true;
                    }

                    else if (event.key.code == sf::Keyboard::Escape) {
                        toggleConsole = false;
                        console.clear();
                    }
                    else if (event.key.code == sf::Keyboard::Enter && toggleConsole) {
                        console.processInput(&player, &window);
                        toggleConsole = false;
                        console.clear();
                    }
            }
            
        }
        
        sf::Time elapsedTime = clock.restart();
        float tempSpeed = elapsedTime.asSeconds() * movSpeed;

        
        if (!toggleConsole) {
            //MOVEMINT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                //std::cout << "Pressed W" << player.position.y << " "<<player.chunkPosition.y<< std::endl;
                player.setPosition(sf::Vector2f(player.position.x, player.position.y - tempSpeed));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                //std::cout << "Pressed D" << player.position.x << " " << player.chunkPosition.x << std::endl;
                player.setPosition(sf::Vector2f(player.position.x + tempSpeed, player.position.y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                //std::cout << "Pressed A" << player.position.x << " " << player.chunkPosition.x << std::endl;
                player.setPosition(sf::Vector2f(player.position.x - tempSpeed, player.position.y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                //std::cout << "Pressed S" << player.position.y << " " << player.chunkPosition.y << std::endl;
                player.setPosition(sf::Vector2f(player.position.x, player.position.y + tempSpeed));
            }
        }

        window.clear(sf::Color::Black);
        window.setView(player.view);

        mouse.updateBlockBreak();
        mouse.updateBlockPlace();

        if (player.chunkPosition.x != player.oldChunkPosition.x || player.chunkPosition.y != player.oldChunkPosition.y) {
           
            chunkLoader.loadChunksToBuffer(&player, true);

            //std::thread t1(&ChunkLoader::loadChunksToBuffer, &chunkLoader, &player, true);
            //t1.join();

            player.oldChunkPosition.x = player.chunkPosition.x;
            player.oldChunkPosition.y = player.chunkPosition.y;
        }

        renderer.renderChunkBuffer(world);
        
        if (toggleDebugInformation) {
            renderer.renderChunkBorders(world);
        }
        renderer.renderPlayer(&player);

        mouse.updateHighlighting(&window);

        //Render GUI
        window.setView(window.getDefaultView());
        if (toggleDebugInformation) {
            renderer.renderDebugInformation(&player, &fps);
        }


        //Render Console
        if (toggleConsole) {
            renderer.renderConsole(&console);
        }
        
        fps.update();
        
        window.display();
    }
}