//
// Created by Tamar M on 2019-10-29.
//

#include "Game.h"
#include <iostream>

using namespace std;

int main() {

    Game* game = new Game( );

    StateChange stateChange = StateChange(game);

    game->initialize();

    game->startup();

    game->mainGameLoop();

    game->computeScore();

    cout << "break here for debug ending" << endl;

}