//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"
#include <iostream>
#include <map>

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

void Map::addAdjacency(const string& from, const string& to)
{
    Country* f;
    Country* t;
    for (auto & elem : countries)
    {
        std::cout << elem << ' ';
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
    }

    pair<Country*, Country*> link = make_pair(f, t);
    adjacencies.push_back(link);
}

