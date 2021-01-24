#include "Game.h"


int main(int argc, char* argv[]) {
    //TO:DO
    //- clean up world saving and loading
    //- add console output textfield
    //- fix loadWorld command; it is accapting invalid world names leading to wierd behavior

    Game game;



    while (game.running())
    {
        //Update
        game.update();

        //Render
        game.render();
        
    }
}