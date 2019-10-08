//
// Created by Tamar M on 2019-09-25.
//

#include <iostream>
#include "Player.h"
#include "../Maps/Map.h"

using namespace std;

Player::Player(Map *map, string playerName, int diskNum, int tokenNum, int armyNum) {
    disks = new int(diskNum);
    tokens = new int(tokenNum);
    armies = new int(armyNum);
    name = new string(playerName);

    citiesIn = new vector<countryValue>;
    for (auto country : *(map->countries)) {
        citiesIn->push_back(make_pair(country.first, 0));
    }

    armiesIn = new vector<countryValue>;
    for (auto country : *(map->countries)) {
        armiesIn->push_back(make_pair(country.first, 1));
    }

    this->map = map;

}

bool Player::PayCoin(int coins) {
    cout << "... Pay " << coins << endl;
    if(*tokens<coins){
        cout << "Player cannot afford that many coins." << endl;
        return false;
    }
    else{
        cout << "Player payed." << endl;
        *tokens-=coins;
        return true;
    }
}

bool Player::PlaceNewArmies(int armiesNum, Country *country) {
    cout << "...Move... Place " << armiesNum << " new armies in " << *(country->name) << endl;
    if(*armies < armiesNum) {
        cout << "Player does not have enough armies to place." << endl;
        return false;
    }

    countryValue *cityIn = getCitiesInCountry(country);
    if (cityIn->first == country) {
        if (cityIn->second <= 0) {
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
    cout << "...Move... Move " << armiesNum << " armies from " << *(from->name) << " to " << *(to->name) << endl;
    countryValue *armyInTo = getArmiesInCountry(to);
    countryValue *armyInFrom = getArmiesInCountry(from);

    if (!map->isAdjacent(to, from)) {
        cout << *(to->name) << " and " << *(from->name) << " are not adjacent." << endl;
        return false;
    }

    if (armyInTo->second < armiesNum) {
        cout << "Not enough armies to move." << endl;
        return false; //there are not enough to country to move
    } else {
        armyInTo->second+= armiesNum;
        armyInFrom->second-=armiesNum;
        cout << "Moved " << armiesNum << " armies from " << *(from->name) << " to " << *(to->name) << endl;
        return true;
    }

}

bool Player::BuildCity(Country *country) {
    cout << "...Move... Build a city in " << *(country->name) << endl;
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

bool Player::MoveOverLand(int armiesNum, Country *to, Country *from) {
    cout << "...Move... Move " << armiesNum << " armies from " << *(from->name) << " to " << *(to->name) << endl;
    countryValue *armyInTo = getArmiesInCountry(to);
    countryValue *armyInFrom = getArmiesInCountry(from);

    if (!map->isAdjacent(to, from)) {
        cout << *(to->name) << " and " << *(from->name) << " are not adjacent." << endl;
        return false;
    }

    if (armyInFrom->second < armiesNum) {
        cout << "Not enough armies to move." << endl;
        return false; //there are not enough to country to move
    } else {
        armyInTo->second+= armiesNum;
        armyInFrom->second-=armiesNum;
        cout << "Moved " << armiesNum << " armies from " << *(from->name) << " to " << *(to->name) << endl;
        return true;
    }

}

bool Player::DestroyArmy(Country *country, Player *player) {
    cout << "...Move... Destroy an army from " << *(player->name) << " in " << *(country->name) << endl;

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
    cout << "》" << *name << endl;
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
    countryValue *armyIn = getArmiesInCountry(country);
    if (armyIn->second > 0 ) {
        *armies+=1;
        armyIn->second--;
    }
    else {
        cout << "There are no armies from this player in this country." << endl;
    }
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

