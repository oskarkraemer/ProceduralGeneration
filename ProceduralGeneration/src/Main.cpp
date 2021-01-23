#include "Game.h"


int init(int argc, char* argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("latest.log", loguru::Append, loguru::Verbosity_WARNING);

    return 0;
}

int main(int argc, char* argv[]) {
    //TO:DO
    //- fix perlin noise between chunks, it cuts off at the chunk borders
    //- clean up world saving and loading
    //- fix create world black screen
    
    init(argc, argv);
    Game game;



    while (game.running())
    {
        //Update
        game.update();

        //Render
        game.render();
        
    }
}