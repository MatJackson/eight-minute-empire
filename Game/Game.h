//
// Created by Tamar M on 2019-10-29.
//

#ifndef EIGHT_MINUTE_EMPIRE_GAME_H
#define EIGHT_MINUTE_EMPIRE_GAME_H

#include "../Maps/Map.h"
#include "../Maps/MapLoader.h"
#include "../Players/Player.h"

using namespace std;

class Game {
public:
    vector<Player*> *players;
    Map* map;
    Deck* deck;

    Game();
    void initialize();
    void startup();
};


#endif //EIGHT_MINUTE_EMPIRE_GAME_H
