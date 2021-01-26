#include "Game.h"

void Game::initLogging()
{
    
    loguru::add_file("latest.log", loguru::Append, loguru::Verbosity_WARNING);
}

//Private functions
void Game::initVariables()
{
	this->window = nullptr;
    this->world = nullptr;
    this->player = nullptr;
    this->renderer = nullptr;
    this->chunkLoader = nullptr;
    this->mouse = nullptr;
}

void Game::initWindow()
{
    if (Globals::isFullscreen) {
        this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "ProceduralGeneration", sf::Style::Fullscreen);
    }
    else {
        this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "ProceduralGeneration", sf::Style::Titlebar | sf::Style::Close);
    }

   this->window->setFramerateLimit(144);

}

void Game::initGameObjects()
{
    this->world = new World;
    this->player = new Player("PizzaHannes");
    this->renderer = new Renderer(window);
    this->chunkLoader = new ChunkLoader(world, renderer, &tr);
    this->mouse = new Mouse(world, renderer, chunkLoader, player);
}

//Constructors / Destructors
Game::Game() {
    this->initLogging();
    this->initVariables();
    this->initWindow();
    this->initGameObjects();
}

Game::~Game()
{
    delete this->window;
    delete this->world;
    delete this->player;
    delete this->renderer;
    delete this->chunkLoader;
    delete this->mouse;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

//Functions
void Game::update()
{
    this->pollEvents();

    sf::Time delta =clock.restart();
    if (!this->toggleConsole) {
        player->updateMovement(delta);
    }
}

void Game::pollEvents()
{
    while (this->window->pollEvent(ev))
    {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->player->savePlayer(world);
                this->window->close();
                break;

            case sf::Event::TextEntered:
                if (toggleConsole) {
                    if (this->ev.text.unicode == '\b') {
                        if (console.input.getSize() > 0) {
                            console.input.erase(console.input.getSize() - 1, 1);
                        }
                    }
                    else if (this->ev.text.unicode > 30 && (this->ev.text.unicode < 127 || this->ev.text.unicode > 159)) {
                        console.input += this->ev.text.unicode;
                    }

                }
                break;


            case sf::Event::KeyReleased:
                switch (this->ev.key.code) {
                    case sf::Keyboard::F3:
                        toggleDebugInformation = !toggleDebugInformation;
                        break;
                    case sf::Keyboard::T:
                        toggleConsole = true;
                        break;
                    case sf::Keyboard::Escape:
                        toggleConsole = false;
                        console.clear();
                        break;
                    case sf::Keyboard::Enter:
                        if (toggleConsole) {
                            toggleConsole = false;
                            console.clear();
                        }
                        break;
                }
                break;

            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::V) {
                    if (this->ev.key.control) {
                        console.input = sf::Clipboard::getString();
                    }
                }


            case sf::Event::MouseWheelMoved:
                if (this->player->selectedItem == 0 && this->ev.mouseWheel.delta == 1) {

                }
                else if (this->player->selectedItem == 7 && this->ev.mouseWheel.delta == -1) {

                }
                else {
                    this->player->selectedItem += this->ev.mouseWheel.delta * -1;
                }
                break;
        }

    }
}

void Game::render()
{

    /*
        Renders the game objects.
    */

    this->window->clear(sf::Color::Black);
    this->window->setView(this->player->view);

    this->mouse->updateBlockBreak();
    this->mouse->updateBlockPlace();

    if (this->player->chunkPosition.x != this->player->oldChunkPosition.x || this->player->chunkPosition.y != this->player->oldChunkPosition.y) {

        if (this->world->loaded) {
            this->chunkLoader->loadChunksToBuffer(this->player, true);

            this->player->oldChunkPosition.x = this->player->chunkPosition.x;
            this->player->oldChunkPosition.y = this->player->chunkPosition.y;
        }
    }


    this->renderer->renderChunkBuffer(this->world);


    if (this->toggleDebugInformation) {
        this->renderer->renderChunkBorders(this->world);
    }
    this->renderer->renderPlayer(this->player);

    this->mouse->updateHighlighting(this->window);

    //Render GUI
    this->window->setView(this->window->getDefaultView());

    if (this->toggleDebugInformation) {
        renderer->renderDebugInformation(this->player, &this->fps);
    }

    this->renderer->renderHotbar(this->player);

    //Render Console
    if (this->toggleConsole) {
        this->renderer->renderConsole(&this->console);
    }

    //Update FPS class
    this->fps.update();

    window->display();
}
