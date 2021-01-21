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
    //- fix world loading and creating bug

    World* world = new World;
    //world->name = "pommes";
    //world->loadWorld();



    //Initialize Player
    Player player("PizzaHannes");
    
    //player.loadPlayer(world);


    FPS fps;
    TerrainGeneration tr;
    sf::RenderWindow window;
    

    if (isFullscreen) {
        window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProceduralGeneration", sf::Style::Fullscreen);

    }
    else {
        window.create(sf::VideoMode(1920, 1080), "ProceduralGeneration", sf::Style::Titlebar | sf::Style::Close);
    }
    

    window.setFramerateLimit(144);

    Renderer renderer(&window);
    if (!renderer.font.loadFromFile("./res/Roboto-Regular.ttf")) {
        return 1;
    }

    ChunkLoader chunkLoader(world, &renderer, &tr);

    Mouse mouse(world, &renderer, &chunkLoader, &player);

    Console console;


    

    bool toggleDebugInformation = false;
    bool toggleConsole = false;
    

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
                    player.savePlayer(world);
                    window.close();
                    break;

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
                    break;


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
                        console.processInput(&player, &window, world);
                        toggleConsole = false;
                        console.clear();
                    }
                    break;


                case sf::Event::MouseWheelMoved:
                    if (player.selectedItem == 0 && event.mouseWheel.delta == 1) {

                    }
                    else if (player.selectedItem == 7 && event.mouseWheel.delta == -1) {

                    }
                    else {
                        player.selectedItem += event.mouseWheel.delta * -1;
                    }
                    break;
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
           
            if (world->loaded) {
                chunkLoader.loadChunksToBuffer(&player, true);


                //std::thread t1(&ChunkLoader::loadChunksToBuffer, &chunkLoader, &player, true);
                //t1.join();

                player.oldChunkPosition.x = player.chunkPosition.x;
                player.oldChunkPosition.y = player.chunkPosition.y;
            }
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

        renderer.renderHotbar(&player);

        //Render Console
        if (toggleConsole) {
            renderer.renderConsole(&console);
        }
        
        fps.update();
        
        window.display();
    }
}