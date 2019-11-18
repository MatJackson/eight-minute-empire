//
// Created by Tamar M on 2019-09-25.
//

#include <iostream>
#include <limits>
#include "Player.h"
#include "../Maps/Map.h"
#include <iomanip>

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
        armiesIn->push_back(make_pair(country.first, 0));
    }

    this->map = map;

    bidding = new BiddingFacility(tokens);
    hand = new vector<Card*>;

    age = new int(0);
    score = new Score();
    score->continentScore = new int(0);
    score->regionScore = new int(0);
    score->goodScore = new int(0);

    setStrategy(new HumanStrategy);

}

void Player::setStrategy(PlayerStrategy* playerStrategy) {
    strategy = playerStrategy;
}

int Player::pickCard(Hand *hand) {
    return (strategy->pickCard(hand));
}

bool Player::PayCoin(int coins) {
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

int Score::getTotalScore() {
    return *continentScore + *regionScore + *goodScore;
}

bool Player::PlaceNewArmies(int armiesNum, Country *country, bool forceAdd) {

    if (!forceAdd) {
        if (*armies < armiesNum) {
            cout << "Player does not have enough armies to place." << endl;
            return false;
        }
        countryValue *cityIn = getCitiesInCountry(country);
        if (cityIn->first == country) {
            if (cityIn->second <= 0 && country != map->startingRegion) {
                cout << "Player does not have cities in that country. Cannot place armies." << endl;
                return false;
            }
        }
        *armies -= armiesNum;
    }

    countryValue *armyIn = getArmiesInCountry(country);
    armyIn->second+=armiesNum;

    cout << "Placed " << armiesNum << " new armies in " << *(country->name) << endl;
    return true;

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

bool Player::MoveArmies(int armiesNum, Country *to, Country *from) {
    countryValue *armyInTo = getArmiesInCountry(to);
    countryValue *armyInFrom = getArmiesInCountry(from);

    if (map->isAdjacent(to, from)==-1) {
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

bool Player::MoveOverLand(int armiesNum, Country *to, Country *from) {

    int adjacency = map->isAdjacent(to, from);
    if (adjacency == -1) {
        cout << *(to->name) << " and " << *(from->name) << " are not adjacent." << endl;
        return false;
    }
    if (adjacency == 1 ) {
        cout << "You can only move from " << *(from->name) << " to " << *(to->name) << " by water." << endl;
        return false;
    }

    return MoveArmies(armiesNum, to, from);

}

bool Player::MoveOverWater(int armiesNum, Country *to, Country *from) {

    int adjacency = map->isAdjacent(to, from);
    if (adjacency == -1) {
        cout << *(to->name) << " and " << *(from->name) << " are not adjacent." << endl;
        return false;
    }
    if (adjacency == 0 ) {
        cout << "You can only move from " << *(from->name) << " to " << *(to->name) << " by land." << endl;
        return false;
    }

    return MoveArmies(armiesNum, to, from);

}

bool Player::DestroyArmy(Country *country, Player *player) {

    countryValue *armyIn = getArmiesInCountry(country);

    if (armyIn->second > 0) {
        cout << "Destroyed army of " << *(player->name) << " in " << *(country->name) << endl;
        player->armyDestroyed(country);
        return true;
    }

    else {
        cout << "Cannot destroy an army of another player where player has no armies." << endl;
    }

    return false;

}

bool Player::Ignore() {
    return false;
}

void Player::display() {
    cout << "\n----------- " << *name << " ---------------------------------" << endl;
    cout << left <<  setw(10) << "Disks: " << *disks << endl;
    cout << left <<  setw(10) << "Tokens: " << *tokens << endl;
    cout << left <<  setw(10) << "Armies: " << *armies << endl;
    cout << "\nArmies in:\t";
    vector<countryValue>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        cout << "\t" << *(i->first->name) << ": " << i->second;
    }
    cout << "\nCities in:\t";
    vector<countryValue>::iterator t;
    for (t = (citiesIn)->begin(); t !=(citiesIn)->end(); ++t) {
        cout << "\t" << *(t->first->name) << ": " << t->second;
    }
    cout << "\n\n" << endl;
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

void Player::setDisks(int disk) {
    *disks = disk;
}

void Player::setTokens(int token) {
    *tokens = token;
}

void Player::setArmies(int army) {
    *armies = army;
}

void Player::printGoods() {
    int ruby = 0;
    int wood = 0;
    int carrot = 0;
    int anvil = 0;
    int ore = 0;
    int wild = 0;

    for (auto card : *hand) {
        switch (card->good.type) {
            case Good::GoodType::GOOD_RUBY :
                ruby += card->good.count;
                break;
            case Good::GoodType::GOOD_WOOD :
                wood += card->good.count;
                break;
            case Good::GoodType::GOOD_CARROT :
                carrot += card->good.count;
                break;
            case Good::GoodType::GOOD_ANVIL :
                anvil += card->good.count;
                break;
            case Good::GoodType::GOOD_ORE :
                ore += card->good.count;
                break;
            case Good::GoodType::GOOD_WILD :
                wild += card->good.count;
                break;
        }
    }

    cout << "\tYou have the following goods:" << endl;
    cout << "\tRuby: " << ruby << endl;
    cout << "\tWood: " << wood << endl;
    cout << "\tCarrot: " << carrot << endl;
    cout << "\tAnvil: " << anvil << endl;
    cout << "\tOre: " << ore << endl;
    cout << "\tWild: " << wild << endl;


}

void Player::computeTotalGoodScore() {
    int ruby = 0;
    int wood = 0;
    int carrot = 0;
    int anvil = 0;
    int ore = 0;
    int wild = 0;

    for (auto card : *hand) {
        switch (card->good.type) {
            case Good::GoodType::GOOD_RUBY :
                ruby += card->good.count;
                break;
            case Good::GoodType::GOOD_WOOD :
                wood += card->good.count;
                break;
            case Good::GoodType::GOOD_CARROT :
                carrot += card->good.count;
                break;
            case Good::GoodType::GOOD_ANVIL :
                anvil += card->good.count;
                break;
            case Good::GoodType::GOOD_ORE :
                ore += card->good.count;
                break;
            case Good::GoodType::GOOD_WILD :
                wild += card->good.count;
                break;
        }
    }

    if (wild > 0) {
        cout << endl;
        cout << *name << ", You have " << wild << " wildcards, please assign your wildcards" << endl;
        cout << "Goodlist: ruby, wood, carrot, anvil, ore" << endl;
        while (wild > 0) {
            string good;
            cout << "Enter a good type: ";
            cin >> good;

            if (good == "ruby") {
                ruby++;
                wild--;
            }

            if (good == "wood") {
                wood++;
                wild--;
            }

            if (good == "carrot") {
                carrot++;
                wild--;
            }

            if (good == "anvil") {
                anvil++;
                wild--;
            }

            if (good == "ore") {
                ore++;
                wild--;
            }
        }
    }

    switch (ruby) {
        case 0:
            break;
        case 1:
            (*score->goodScore) += 1;
            break;
        case 2:
            (*score->goodScore) += 2;
            break;
        case 3:
            (*score->goodScore) += 3;
            break;
        default: // default handle cases where ruby > 3
            (*score->goodScore) += 6;
    }

    switch (wood) {
        case 0:
            break;
        case 1:
        case 2:
            (*score->goodScore) += 1;
            break;
        case 3:
        case 4:
            (*score->goodScore) += 2;
            break;
        case 5:
            (*score->goodScore) += 3;
            break;
        default: // default handle cases where wood > 5
            (*score->goodScore) += 6;

    }

    switch (carrot) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            (*score->goodScore) += 1;
            break;
        case 4:
        case 5:
            (*score->goodScore) += 2;
            break;
        case 6:
        case 7:
            (*score->goodScore) += 3;
            break;
        default: // default handle cases where carrot > 7
            (*score->goodScore) += 6;

    }

    switch (anvil) {
        case 0:
            break;
        case 1:
        case 2:
            (*score->goodScore) += 1;
            break;
        case 3:
        case 4:
            (*score->goodScore) += 2;
            break;
        case 5:
        case 6:
            (*score->goodScore) += 3;
            break;
        default: // default handle cases where anvil > 6
            (*score->goodScore) += 6;
    }

    switch (ore) {
        case 0:
            break;
        case 1:
        case 2:
            (*score->goodScore) += 1;
            break;
        case 3:
            (*score->goodScore) += 2;
            break;
        case 4:
            (*score->goodScore) += 3;
            break;
        default: // default handle cases where ore > 5
            (*score->goodScore) += 6;
    }
}

