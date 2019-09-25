//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"
#include <iostream>
#include <list>

using namespace std;

Map::Map()
{
    countries={};
    adjacencies={};
}

void Map::addCountry(const string& name, const string& continent)
{
    Country *newCountry = new Country(name, continent);
    countries.push_back(newCountry);
}

bool Map::addAdjacency(const string& from, const string& to)
{
    Country* f;
    Country* t;
    for (auto & elem : countries)
    {
        if (elem->name == from)
        {
            f = elem;
        }
        if (elem->name == to)
        {
            t = elem;
        }
    }

    if (f == nullptr || t == nullptr) {
        cout<<"ERROR";
        return false;
    }

    pair<Country*, Country*> link = make_pair(f, t);
    adjacencies.push_back(link);

    return true;
}

bool Map::isValid()
{
    return  isConnected() && isContinentsConnected() && isCountryOneContinent();
}

bool Map::isConnected()
{

}

bool Map::isContinentsConnected()
{

}

bool Map::isCountryOneContinent()
{

}


