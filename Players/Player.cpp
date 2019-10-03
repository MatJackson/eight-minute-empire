//
// Created by Tamar M on 2019-09-25.
//

#include <iostream>
#include "Player.h"
#include "../Maps/Map.h"

using namespace std;

Player::Player(Map *map, int diskNum, int tokenNum, int armyNum) {
    disks = new int(diskNum);
    tokens = new int(tokenNum);
    armies = new int(armyNum);

    citiesIn = new vector<countryValue>;
    for (auto country : (map->getCountries())) {
        citiesIn->push_back(make_pair(country, 50));
    }

    armiesIn = new vector<countryValue>;
    for (auto country : (map->getCountries())) {
        armiesIn->push_back(make_pair(country, 50));
    }

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

bool Player::PlaceNewArmies(int armiesNum, Country *country)
{
    if(*armies < armiesNum) {
        cout << "Player does not have enough armies to place." << endl;
        return false;
    }

    bool cityExists = false;

    vector<countryValue>::iterator i;
    for (i = (citiesIn)->begin(); i !=(citiesIn)->end(); ++i) {
        if (i->first == country) {
            if (i->second > 0) {
                cityExists = true;
            }
        }
    }

    if(!cityExists) {
        cout << "Player does not have cities in that country. Cannot place armies." << endl;
        return false;
    }

    else{
        *armies -= armiesNum;
        vector<countryValue>::iterator i;
        for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
            if (i->first == country) {
                i->second+=armiesNum;
            }
        }
        cout << "Placed " << armiesNum << " new armies in " << *(country->name) << endl;
        return true;
    }
}

bool Player::MoveArmies(int armiesNum, Country *to, Country *from)
{
    vector<countryValue>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        if (i->first == to) {
            if (i->second < armiesNum) {
                cout << "Not enough armies to move." << endl;
                return false; //there are not enough to country to move
            } else {
                vector<countryValue>::iterator t;
                for (t = (armiesIn)->begin(); t != (armiesIn)->end(); ++t) {
                    if (t->first == to) {
                        t->second -= armiesNum;
                    }
                    if (t->first == from) {
                        t->second += armiesNum;
                    }
                }
                cout << "Moved " << armiesNum << " armies from " << *(from->name) << " to " << *(to->name) << endl;
                return true;
            }
        }
    }

    return false;
}

bool Player::BuildCity(Country *country)
{
    if(*disks < 1) {
        cout << "Not enough disks." << endl;
        return false;
    }

    vector<countryValue>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        if (i->first == country) {
            if (i->second > 0) {
                vector<countryValue>::iterator i;
                for (i = (citiesIn)->begin(); i !=(citiesIn)->end(); ++i) {
                    if (i->first == country) {
                        i->second++;
                        cout << "Built a new city in " << *(country->name) << endl;
                        (*disks)--;
                        return true;
                    }
                }
            }
            else {
                cout << "Cannot build city where player does not have an army." << endl;
            }
        }
    }

    return false;
}

void Player::display()
{
    cout << "》 Number of disks left: " << *disks << endl;
    cout << "》 Number of token left: " << *tokens << endl;
    cout << "》 Number of armies left: " << *armies << endl;
    cout << "》 Armies in: " << endl;
    vector<countryValue>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        cout << "》   " << *(i->first->name) << ": " << i->second << endl;
    }
    cout << "》 Cities in: " << endl;
    vector<countryValue>::iterator t;
    for (t = (citiesIn)->begin(); t !=(citiesIn)->end(); ++t) {
        cout << "》   " << *(t->first->name) << ": " << t->second << endl;
    }
}

int Player::getDisks()
{
    return *disks;
}

int Player::getTokens()
{
    return *tokens;
}

int Player::getArmies()
{
    return *armies;
}

