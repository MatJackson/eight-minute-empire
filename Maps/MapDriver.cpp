//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"
#include <iostream>

using namespace std;

int main() {
    Map map = Map();
    map.addCountry("Canada", "NA");
    map.addCountry("US", "NA");
    map.addCountry("HI", "NA");
    map.addAdjacency("Canada", "US");

    vector<Country*>::iterator i;
    for (i = (map.countries).begin(); i !=(map.countries).end(); ++i)
    {
        cout << (*i)->name + " ";
    }

}