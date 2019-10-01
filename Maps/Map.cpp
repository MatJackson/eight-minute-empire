//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"

using namespace std;

Map::Map()
{
    countries = new vector<Country*>();
    adjacencies = new vector<adjacent>();
}

Map::~Map()
{

}

void Map::addCountry(Country &country)
{
    countries->push_back(&country);
}

bool Map::addAdjacency(Country &from, Country &to)
{
    auto fromExists = find(countries->begin(), countries->end(), &from);
    auto toExists = find(countries->begin(), countries->end(), &to);

    if (fromExists == countries->end() || toExists == countries->end()) { //if either one not found
        return false;
    }

    pair<Country*, Country*> link = make_pair(&from, &to);
    adjacencies->push_back(link);

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


