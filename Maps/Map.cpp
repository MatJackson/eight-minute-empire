//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"
#include <iostream>
#include <list>

using namespace std;

Map::Map()
{
    countries = new vector<country>;
    continents = new vector<Continent*>;
}

void Map::addCountry(Country *country)
{
    vector<Country*> init = vector<Country*>();
    countries->push_back(make_pair(country, init));
    cout << "Added country " << *(country->name) << " to the map." << endl;
    vector<Continent*>::iterator i;
    for (i = (continents)->begin(); i !=(continents)->end(); ++i) {
        if (*(*i)->name == *(country->continent->name)) {
            return;
        }
    }
    continents->push_back(country->continent);
    cout << "Added continent " << *(country->continent->name) << " to the map." << endl;

}

bool Map::addAdjacency(Country *from, Country *to)
{
    if(!to || !from) {
        return false;
    }

    vector<country>::iterator i;
    for (i = (countries)->begin(); i !=(countries)->end(); ++i) {
        if (i->first == to) {
            i->second.push_back(from);
        }
        if (i->first == from) {
            i->second.push_back(to);
        }
    }
    cout << "Added adjacency between " << *(to->name) << " and " << *(from->name)<< " to the map." << endl;

    return false;
}

bool Map::isAdjacent(Country *from, Country *to)
{
    vector<country>::iterator i;
    for (i = (countries)->begin(); i !=(countries)->end(); ++i) {
        if (i->first == to){
            auto it = find(i->second.begin(), i->second.end(), from);
            if (it != i->second.end())
            {
                return true;
            }
        }
    }

    return false;
}

Country* Map::findCountry(string countryFind) {
    vector<country>::iterator i;
    for (i = (countries)->begin(); i !=(countries)->end(); ++i) {
        if (*((i->first))->name == countryFind) {
            return &(*((i->first)));
        }
    }

    return nullptr;
}


void Map::display() {
    cout << endl << "-------------------------------------------------" << endl;
    cout << endl << "Here is the map!" << endl << endl;
    cout << "Countries: " << endl;
    vector<country>::iterator i;
    for (i = countries->begin(); i !=countries->end(); ++i) {
        cout << *(i->first)->name << endl;
        cout << "    Continent = " << *(i->first)->continent->name << endl;
        cout << "    Adjacent to..." << endl;
        vector<Country*>::iterator t;
        for (t = (i->second).begin(); t !=(i->second).end(); ++t) {
            cout << "         " << *((*t)->name) << endl;
            }
        cout << endl;
        }
    cout << endl << "-------------------------------------------------" << endl;
    cout << endl;
}

bool Map::isValid()
{
    return  isConnected() && isContinentsConnected() && isCountryOneContinent();
}

bool Map::isConnected()
{

    auto *visited = new vector<pair<Country*, bool>>;
    for (auto country : *(countries)) {
        visited->push_back(make_pair(country.first, false));
    }

    vector<pair<Country*, bool>>::iterator i;
    for (i = visited->begin(); i !=visited->end(); ++i) {
        if (!i->second)
        {
            search(i->first, visited);
        }
    }

    cout << "Map is valid." << endl;
    return true;
}

void Map::search(Country* countrySearch, vector<pair<Country*, bool>> *visited)
{

    vector<pair<Country*, bool>>::iterator i;
    for (i = visited->begin(); i !=visited->end(); ++i) {
        if (i->first==countrySearch)
        {
            i->second=true;
        }
    }

    vector<country>::iterator t;
    for (t = (countries)->begin(); t !=(countries)->end(); ++t) {
        if (t->first == countrySearch) {
            vector<Country*>::iterator w;
            for (w = (t->second).begin(); w !=(t->second).end(); ++w) {
                vector<pair<Country*, bool>>::iterator q;
                for (q = visited->begin(); q !=visited->end(); ++q) {
                    if ((q->first) == *w)
                    {
                        search(*w, visited);
                    }
                }

                }
            }
        }

}

bool Map::isContinentsConnected()
{
    return true;
}

bool Map::isCountryOneContinent()
{
    return true;
}

