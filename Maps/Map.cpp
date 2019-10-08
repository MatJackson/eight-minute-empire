//
// Created by Tamar M on 2019-09-20.
//

#include <algorithm>
#include "Map.h"
#include <iostream>

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
        if (*(*i)->name == *(country->continent->name)) {
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

Country* Map::findCountry(string country) {
    vector<Country*>::iterator i;
    for (i = (countries)->begin(); i !=(countries)->end(); ++i) {
        if (*(*i)->name == country) {
            return &(*(*i));
        }
    }
}

void Map::display() {
    cout << endl << "Here is the map!" << endl << endl;
    cout << "Countries: " << endl;
    vector<Country*>::iterator i;
    for (i = countries->begin(); i !=countries->end(); ++i) {
        cout << "   " + *(*i)->name << " in continent " << *(*i)->continent->name << endl;
    }

    cout << endl << "Adjacencies: " << endl;
    vector<pair<Country*, Country*>>::iterator t;
    for (t = adjacencies->begin(); t !=adjacencies->end(); ++t) {
        cout << "   " + *(t)->first->name + " " + *(t)->second->name << endl;
    }
}

bool Map::isValid()
{
    return  isConnected() && isContinentsConnected() && isCountryOneContinent();
}

bool Map::isConnected()
{
    return true;
}

bool Map::isContinentsConnected()
{
    return true;
}

bool Map::isCountryOneContinent()
{
    return true;
}

vector<Country*> Map::getCountries()

{
    return *countries;
}

vector<adjacent> Map::getAdjacencies()
{
    return *adjacencies;
}


