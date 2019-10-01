//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"
#include <iostream>

using namespace std;

int main() {
    Map map = Map();

    Continent *north = new Continent("North");

    Country *usa = new Country("usa", *north);
    Country *can = new Country("can", *north);

    map.addCountry(*usa);
    map.addCountry(*can);

    map.addAdjacency(*usa, *can);

    vector<Country*>::iterator i;
    for (i = (map.countries)->begin(); i !=(map.countries)->end(); ++i)
    {
        cout << *((*i)->name);
    }

}