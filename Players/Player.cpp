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
        armiesIn->push_back(make_pair(country.first, 0));
    }

    this->map = map;

    bidding = new BiddingFacility(tokens);
    hand = new vector<Card*>;

    age = new int(0);

}

bool Player::playCard(Card& card) {

    cout << "NEW CARD SELECTED! " << endl;
    card.printCard();

    if(card.combinationType==0) {
        playAction(card.actions[0]);
    }
    else {
        AndOrAction(card.combinationType, card.actions);
    }

    return true;
}

bool Player::playAction(Action& action) {

    int count = action.count;
    string countryName;
    int armiesNum;
    bool success;
    string choice;

    do {

        cout << "Write 'ignore' to skip or anything else to proceed. ";
        cin >> choice;
        if(choice=="ignore"){
            return false;
        }

        switch (action.type) {
            case 0 : {
                cout << "Add " << count << " army" << endl;
                Country *country = nullptr;
                while (!country) {
                    cout << "Name country to add armies in: ";
                    cin >> countryName;
                    country = map->findCountry(countryName);
                }
                while (true) {
                    cout << "\nHow many armies to add in country? ";
                    cin >> armiesNum;

                    if (cin.fail() || armiesNum > count || armiesNum <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid number." << endl;
                    } else {
                        break;
                    }
                }
                success = PlaceNewArmies(armiesNum, country);
                if (success) {
                    count -= armiesNum;
                }
            }
                break;
            case 1 : {
                cout << "Move over " << count << " land" << endl;
                Country *from = nullptr;
                while (!from) {
                    cout << "Name country to move armies from: ";
                    cin >> countryName;
                    from = map->findCountry(countryName);
                }
                Country *to = nullptr;
                while (!to) {
                    cout << "Name country to move armies to: ";
                    cin >> countryName;
                    to = map->findCountry(countryName);
                }
                while (true) {
                    cout << "\nHow many armies to move? ";
                    cin >> armiesNum;

                    if (cin.fail() || armiesNum > count || armiesNum <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid number." << endl;
                    } else {
                        break;
                    }
                }
                success = MoveOverLand(armiesNum, to, from);
                if (success) {
                    count -= armiesNum;
                }
            }
                break;
            case 2 : {
                cout << "Move over " << count << " land or water" << endl;
                Country *from = nullptr;
                while (!from) {
                    cout << "Name country to move armies from: ";
                    cin >> countryName;
                    from = map->findCountry(countryName);
                }
                Country *to = nullptr;
                while (!to) {
                    cout << "Name country to move armies to: ";
                    cin >> countryName;
                    to = map->findCountry(countryName);
                }
                while (true) {
                    cout << "\nHow many armies to move? ";
                    cin >> armiesNum;

                    if (cin.fail() || armiesNum > count || armiesNum <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid number." << endl;
                    } else {
                        break;
                    }
                }
                success = MoveArmies(armiesNum, to, from);
                if (success) {
                    count -= armiesNum;
                }
            }
                break;
            case 3 : {
                cout << "Build " << count << " city" << endl;
                Country *country = nullptr;
                while (!country) {
                    cout << "Name country to build a city in: ";
                    cin >> countryName;
                    country = map->findCountry(countryName);
                }
                success = BuildCity(country);
                if (success) {
                    count -= 1;
                }
            }
                break;
            case 4 : {
                cout << "Destroy an army of another player";
            }
                break;
        }

        if (count>0) {
            cout << endl << "You still have " << count << " left... ";
        }

    } while(count>0);

    return true;
}

bool Player::AndOrAction(Card::CombinationType type, vector<Action> actions) {

    cout << "What action would you like to do" << ((type==2) ? " first?" : "?") << " Select by typing the index of the actions (1 or 2).";

        int index;
        while (true) {
            cin >> index;

            if (cin.fail() || index > 2 || index < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid number." << endl;
            } else {
                break;
            }
        }
        playAction(actions[index-1]);
        if(type==1) {
            return true;
        }
        actions.erase(actions.begin()+(index-1));

        cout << "Next action: " << (actions.begin()->getName()) << endl;
        playAction(actions[0]);

    return true;
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

bool Player::PlaceNewArmies(int armiesNum, Country *country) {

    countryValue *cityIn = getCitiesInCountry(country);
    if (cityIn->first == country) {
        if (cityIn->second <= 0 && country!=map->startingRegion) {
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
        cout << "Destroyed army of player in " << *(country->name) << endl;
        player->armyDestroyed(country);
        return true;
    }

    else {
        cout << "Cannot destroy an army of another player where player has no armies." << endl;
    }

    return false;

}

bool Player::Ignore() {
    return true;
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

void Player::setDisks(int disk) {
    *disks = disk;
}

void Player::setTokens(int token) {
    *tokens = token;
}

void Player::setArmies(int army) {
    *armies = army;
}

