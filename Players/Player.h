//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_PLAYER_H
#define EIGHT_MINUTE_EMPIRE_PLAYER_H

#include "../Maps/Map.h"
#include "../Bidding/BiddingFacility.h"
#include "../Cards/Cards.h"

using namespace std;

struct Score {
    int *continentScore;
    int *regionScore;
    int *goodScore;

    int getTotalScore();
};

class Player {

public:
    typedef pair<Country*, int> countryValue;
    Map *map;
    string *name;
    int *disks;
    int *tokens;
    int *armies;
    int *age;
    Score *score;
    BiddingFacility *bidding;
    vector<Card*> *hand;
    vector<countryValue> *citiesIn;
    vector<countryValue> *armiesIn;

    Player(Map *map, string name, int diskNum, int tokenNum, int armyNum);
    bool PayCoin(int coins);
    bool PlaceNewArmies(int armiesNum, Country *country, bool forceAdd);
    bool MoveArmies(int armiesNum, Country *to, Country *from);
    bool MoveOverLand(int armiesNum, Country *to, Country *from);
    bool MoveOverWater(int armiesNum, Country *to, Country *from);
    bool BuildCity(Country *country);
    bool DestroyArmy(Country *country, Player *player);
    bool Ignore();
    void display();
    pair<Country*, int>* getArmiesInCountry(Country *country);
    pair<Country*, int>* getCitiesInCountry(Country *country);
    void armyDestroyed(Country* country);
    void setDisks(int disk);
    void setTokens(int token);
    void setArmies(int army);
    void printGoods();
    void computeTotalGoodScore();
};

#endif //EIGHT_MINUTE_EMPIRE_PLAYER_H
