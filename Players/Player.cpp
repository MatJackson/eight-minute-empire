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
        citiesIn->push_back(make_pair(country, 1));
    }

    armiesIn = new vector<countryValue>;
    for (auto country : (map->getCountries())) {
        armiesIn->push_back(make_pair(country, 1));
    }

}

bool Player::PayCoin(int coins) {
    if(*tokens<coins){
        cout << "Player cannot afford that many coins.";
        return false;
    }
    else{
        *tokens-=coins;
        return true;
    }
}

bool Player::PlaceNewArmies(int armiesNum, Country *country) {
    if(*armies < armiesNum) {
        cout << "Player does not have enough armies to place." << endl;
        return false;
    }

    countryValue *cityIn = getCitiesInCountry(country);
    if (cityIn->first == country) {
        if (cityIn->second < 0) {
            cout << "Player does not have cities in that country. Cannot place armies." << endl;
            return false;
        }
    }

    *armies -= armiesNum;
    countryValue *armyIn = getArmiesInCountry(country);
    armyIn->second+=armiesNum;

    cout << "Placed " << armiesNum << " new armies in " << *(country->name) << endl;
    return true;

}

bool Player::MoveArmies(int armiesNum, Country *to, Country *from) {
    countryValue *armyInTo = getArmiesInCountry(to);
    countryValue *armyInFrom = getArmiesInCountry(from);

    if (armyInTo->second < armiesNum) {
        cout << "Not enough armies to move." << endl;
        return false; //there are not enough to country to move
    } else {
        armyInTo->second+= armiesNum;
        armyInFrom->second-=armiesNum;
        cout << "Moved " << armiesNum << " armies from " << *(from->name) << " to " << *(to->name) << endl;
        return true;
    }

    return false;
}

bool Player::BuildCity(Country *country) {
    if(*disks < 1) {
        cout << "Not enough disks." << endl;
        return false;
    }

    countryValue *armyIn = getArmiesInCountry(country);

    if (armyIn->second > 0) {
        *disks-=1;
        countryValue *cityIn = getCitiesInCountry(country);
        cityIn->second++;
        cout << "Built a city in " << *(country->name) << endl;
        return true;
    }

    else {
        cout << "Cannot build a city where player has no armies." << endl;
    }

    return false;
}

void Player::MoveOverLand() {

}

bool Player::DestroyArmy(Country *country, Player *player) {

    countryValue *armyIn = getArmiesInCountry(country);

    if (armyIn->second > 0) {
        cout << "Destroyed army of player in " << *(country->name) << endl;
        player->armyDestroyed(country);
        return true;
    }

    else {
        cout << "Cannot destroy an army of another player where player has no armies." << endl;
    }

    return false;

}

void Player::display() {
    cout << endl << "》 Number of disks left: " << *disks << endl;
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
    cout << endl;
}

pair<Country*, int>* Player::getArmiesInCountry(Country *country) {
    vector<countryValue>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        if (i->first == country) {
            return &(*i);
        }
    }
}

pair<Country*, int>* Player::getCitiesInCountry(Country *country) {
    vector<countryValue>::iterator i;
    for (i = (citiesIn)->begin(); i !=(citiesIn)->end(); ++i) {
        if (i->first == country) {
            return &(*i);
        }
    }
}

void Player::armyDestroyed(Country *country) {
    *armies+=1;
    countryValue *armyIn = getArmiesInCountry(country);
    armyIn->second--;
}

int Player::getDisks() {
    return *disks;
}

int Player::getTokens() {
    return *tokens;
}

int Player::getArmies() {
    return *armies;
}

void Player::setTokens(int token) {
    *tokens+=token;
}

