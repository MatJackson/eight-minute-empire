//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"

using namespace std;
typedef pair<Country*, Country*> adjacent;

Map::Map()
{
    countries = new vector<Country*>();
    adjacencies = new vector<adjacent>();
    continents = new vector<Continent*>();
}

void Map::addCountry(Country *country)
{
    countries->push_back(country);
    vector<Continent*>::iterator i;
    for (i = (continents)->begin(); i !=(continents)->end(); ++i) {
        if (*i == country->continent) {
            return;
        }
    }
    continents->push_back(country->continent);
}

bool Map::addAdjacency(Country *from, Country *to)
{
    auto fromExists = find(countries->begin(), countries->end(), from);
    auto toExists = find(countries->begin(), countries->end(), to);

    if (fromExists == countries->end() || toExists == countries->end()) { //if either one not found
        return false;
    }

    pair<Country*, Country*> link = make_pair(from, to);
    adjacencies->push_back(link);

    return true;
}

bool Map::isAdjacent(Country *from, Country *to)
{
    vector<pair<Country*, Country*>>::iterator i;
    for (i = (adjacencies)->begin(); i !=(adjacencies)->end(); ++i) {
        if ((i->first == to && i->second == from) || i->first == from && i->second == to) {
            return true;
        }
    }

    return false;
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

vector<Country*> Map::getCountries()

{
    return *countries;
}

vector<adjacent> Map::getAdjacencies()
{
    return *adjacencies;
}


