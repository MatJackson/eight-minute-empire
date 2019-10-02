//
// Created by Tamar M on 2019-09-20.
//

#include <iostream>
#include "Map.h"
#include "../Players/Player.h"

using namespace std;

int main() {
    Map *map = new Map();

    Continent *north = new Continent("North");

    Country *usa = new Country("Usa", *north);
    Country *can = new Country("can", *north);

    map->addCountry(*usa);
    map->addCountry(*can);

    map->addAdjacency(*usa, *can);

    vector<Country*>::iterator i;
    for (i = (map->countries)->begin(); i !=(map->countries)->end(); ++i)
    {
        cout << *((*i)->name) + " " << endl;
    }

    Player *player = new Player(*map, 12, 13, 40);
    player->PlaceNewArmies(5, *usa);

}