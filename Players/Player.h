//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_PLAYER_H
#define EIGHT_MINUTE_EMPIRE_PLAYER_H

#include "../Maps/Map.h"

using namespace std;

class Player {

private:
    typedef pair<Country*, int> countryValue;
    string *name;
    int *disks;
    int *tokens;
    int *armies;
    vector<countryValue> *citiesIn;
    vector<countryValue> *armiesIn;

public:
    Player(Map *map, int diskNum, int tokenNum, int armyNum);
    bool PayCoin(int coins);
    bool PlaceNewArmies(int armiesNum, Country *country);
    bool MoveArmies(int armiesNum, Country *to, Country *from);
    void MoveOverLand();
    bool BuildCity(Country *country);
    void DestroyArmy();
    void display();
    int getDisks();
    int getTokens();
    int getArmies();
};

#endif //EIGHT_MINUTE_EMPIRE_PLAYER_H
