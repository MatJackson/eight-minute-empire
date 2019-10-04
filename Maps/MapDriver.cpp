//
// Created by Tamar M on 2019-09-20.
//

#include <iostream>
#include "Map.h"
#include "../Players/Player.h"

using namespace std;

int main() {
    Map *map = new Map();

    auto *north = new Continent("North");

    auto *usa = new Country("USA", north);
    auto *can = new Country("Canada", north);

    map->addCountry(usa);
    map->addCountry(can);

    map->addAdjacency(usa, can);

//    vector<Country*>::iterator i;
//    for (i = (map->getCountries()).begin(); i !=(map->getCountries()).end(); ++i) {
//        cout << *((*i)->name) + " " << endl;
//    }

    Player *player = new Player(map, 12, 13, 40);
    Player *player2 = new Player(map, 12, 13, 40);

    player->display();
    player->DestroyArmy(usa, player2);
    player2->display();
    player->BuildCity(usa);
    player->display();

    player->PlaceNewArmies(5, usa);
    player->display();

    player->MoveArmies(1, usa, can);
    player->display();

}