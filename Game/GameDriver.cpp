//
// Created by Tamar M on 2019-10-29.
//

#include "GameEngine.h"
#include <iostream>

using namespace std;

int main() {

    GameEngine* game = new GameEngine( );

    //ScoreView scoreview = ScoreView(game);
    StateChange stateChange = StateChange(game);

    game->initialize();

    game->startup();

    game->mainGameLoop();

    game->computeWinner();

}