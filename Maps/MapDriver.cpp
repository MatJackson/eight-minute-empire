//
// Created by Tamar M on 2019-09-20.
//

#include <iostream>
#include "Map.h"
#include "../Players/Player.h"

using namespace std;

int main() {
    Map *map = new Map();

    auto *north = new Continent("North America");
    auto *europe = new Continent("Europe");

    auto *usa = new Country("USA", north);
    auto *can = new Country("Canada", north);
    auto *portugal = new Country("Portugal", europe);
    auto *spain = new Country("Spain", europe);
    auto *italy = new Country("Italy", europe);

    map->addCountry(usa);
    map->addCountry(can);
    map->addCountry(portugal);
    map->addCountry(spain);
    map->addCountry(italy);

    map->addAdjacency(usa, can);
    map->addAdjacency(can, portugal);
    map->addAdjacency(spain, portugal);
    map->addAdjacency(spain, italy);


}