//
// Created by Tamar M on 2019-09-25.
//

#include <iostream>
#include "Player.h"
#include "../Maps/Map.h"

using namespace std;

Player::Player(Map &map, int diskNum, int tokenNum, int armyNum) {
    disks = &diskNum;
    tokens = &tokenNum;
    armies = &armyNum;

    armiesIn = new vector<army>;
    for (auto country : *(map.countries)) {
        armiesIn->push_back(make_pair(country, 0));
    }

    citiesIn = new vector<Country*>;
}

bool Player::PayCoin(int coins)
{
    if(*tokens<coins){
        cout << "Player cannot afford that many coins.";
        return false;
    }
    else{
        *tokens-=coins;
        return true;
    }
}

bool Player::PlaceNewArmies(int armiesNum, Country &country)
{
    if(*armies < armiesNum) {
        cout << "Player does not have enough armies to place." << endl;
        return false;
    }

    cout << *armies << endl; //ok

    bool cityExists = false;
    auto it = find(citiesIn->begin(), citiesIn->end(), &country);
    if (it != citiesIn->end()) {
        cityExists=true;
    }

    cout << *armies << endl; //no


    if(!cityExists) {
        cout << "Player does not have cities in that country. Cannot place armies." << endl;
        return false;
    }

    else{
        *armies-=armiesNum;
        country.armies+=armiesNum;
        //add armies in vector
        return true;
    }
}

bool Player::MoveArmies(int armiesNum, Country &to, Country &from)
{
    if(*armies<armiesNum){
        return false;
    }

    vector<army>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        if (i->first == &to) {
            if (i->second < armiesNum)
                return false; //there are not enough to country to move
        } else {
            *armies -= armiesNum;
            (&to)->armies += armiesNum;

            vector<army>::iterator t;
            for (t = (armiesIn)->begin(); t != (armiesIn)->end(); ++t) {
                if (t->first == &to) {
                    t->second -= armiesNum;
                }
                if (t->first == &from) {
                    t->second += armiesNum;
                }
            }

            return true;
        }
    }
}

