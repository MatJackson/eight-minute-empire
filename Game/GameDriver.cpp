//
// Created by Tamar M on 2019-10-29.
//

#include "Game.h"
#include <iostream>

using namespace std;

int main() {

    Game* game = new Game( );

    game->initialize();

    game->startup();

    game->mainGameLoop();

    cout << "break here for debug ending" << endl;

}