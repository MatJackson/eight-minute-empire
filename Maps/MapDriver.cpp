//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"
#include "MapDriver.h"
#include <iostream>

using namespace std;

int run() {
    Map map = Map();
    map.addCountry("Canada", "NA");
    map.addCountry("US", "NA");
    map.addCountry("HI", "NA");
    map.addAdjacency("Canada", "US");

    for (std::vector<Country*>::iterator i = map.countries.begin(); i != map.countries.end(); ++i)
        std::cout << *i << ' ';
}