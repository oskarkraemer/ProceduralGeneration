#include "Game.h"


int main(int argc, char* argv[]) {
    //TO:DO
    //- fix perlin noise between chunks, it cuts off at the chunk borders
    //- clean up world saving and loading
    //- add console output textfield

    Game game;



    while (game.running())
    {
        //Update
        game.update();

        //Render
        game.render();
        
    }
}