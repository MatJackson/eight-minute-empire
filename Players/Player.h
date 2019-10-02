//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_PLAYER_H
#define EIGHT_MINUTE_EMPIRE_PLAYER_H

#include "../Maps/Map.h"

using namespace std;

class Player {

public:
    typedef pair<Country*, int> army;

    int *disks;
    int *tokens;
    int *armies;
    vector<Country*> *citiesIn;
    vector<army> *armiesIn;

    Player(Map &map, int diskNum, int tokenNum, int armyNum);
    bool PayCoin(int coins);
    bool PlaceNewArmies(int armiesNum, Country &country);
    bool MoveArmies(int armiesNum, Country &to, Country &from);
    void MoveOverLand();
    void BuildCity();
    void DestroyArmy();
};

#endif //EIGHT_MINUTE_EMPIRE_PLAYER_H
