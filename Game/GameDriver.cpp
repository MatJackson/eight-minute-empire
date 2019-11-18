//
// Created by Tamar M on 2019-10-29.
//

#include "Game.h"
#include <iostream>

using namespace std;

int main() {

    Game* game = new Game( );

    ScoreView scoreview = ScoreView(game);
    StateChange stateChange = StateChange(game);

    game->initialize();

    game->startup();

    game->mainGameLoop();

    game->computeWinner();

}