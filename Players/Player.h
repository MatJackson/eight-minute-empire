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
    Map *map;

public:
    Player();
    Player(Map *map, string name, int diskNum, int tokenNum, int armyNum);
    bool PayCoin(int coins);
    bool PlaceNewArmies(int armiesNum, Country *country);
    bool MoveArmies(int armiesNum, Country *to, Country *from);
    bool MoveOverLand(int armiesNum, Country *to, Country *from);
    bool BuildCity(Country *country);
    bool DestroyArmy(Country *country, Player *player);
    void display();
    pair<Country*, int>* getArmiesInCountry(Country *country);
    pair<Country*, int>* getCitiesInCountry(Country *country);
    void armyDestroyed(Country* country);
    int getDisks();
    int getTokens();
    int getArmies();
    void setTokens(int token);
};

#endif //EIGHT_MINUTE_EMPIRE_PLAYER_H
