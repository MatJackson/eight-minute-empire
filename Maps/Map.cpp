//
// Created by Tamar M on 2019-09-20.
//

#include "Map.h"
#include <iostream>
#include <list>
#include <iomanip>

using namespace std;

Map::Map()
{
    countries = new vector<country>;
    continents = new vector<continent>;
    startingRegion = nullptr;
}

void Map::addCountry(Country *country)
{
    vector<adjacency> init = vector<adjacency>();
    if(countries->empty()) { startingRegion=country;}
    countries->push_back(make_pair(country, init));
    //cout << "Added country " << *(country->name) << " to the map." << endl;
    vector<continent>::iterator i;
    for (i = (continents)->begin(); i !=(continents)->end(); ++i) {
        if (*(*i).first->name == *(country->continent->name)) {
            (*i).second.push_back(country);
            return;
        }
    }
    vector<Country*> countriesInContinent = vector<Country*>();
    countriesInContinent.push_back(country);
    continents->push_back(make_pair((country->continent), (countriesInContinent)));
    //cout << "Added continent " << *(country->continent->name) << " to the map." << endl;

}

bool Map::addAdjacency(Country *from, Country *to, bool type)
{
    //type is 0 for land and 1 for water
    if(!to || !from) {
        return false;
    }

    vector<country>::iterator i;
    for (i = (countries)->begin(); i !=(countries)->end(); ++i) {
        if (i->first == to) {
            i->second.push_back(make_pair(from, type));
        }
        if (i->first == from) {
            i->second.push_back(make_pair(to, type));
        }
    }

    //cout << "Added adjacency between " << *(to->name) << " and " << *(from->name)<< " to the map." << endl;
    return true;
}

int Map::isAdjacent(Country *from, Country *to)
{
    vector<country>::iterator i;
    for (i = (countries)->begin(); i !=(countries)->end(); ++i) {
        if (i->first == to) {
            vector<adjacency>::iterator t;
            for (t = (i->second).begin(); t != (i->second).end(); ++t) {
                if (t->first == from) {
                    if (t->second == 0)
                        return 0;
                    if (t->second == 1)
                        return 1;
                }
            }
        }
    }

    return -1;
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
    cout << endl << "----------- THE MAP ----------------------------------" << endl;
    cout << left << " " <<  setw(20) << "Country"  << setw(20) << "Continent"   << setw(70) << "Adjacent to..." << endl << endl;
    vector<country>::iterator i;
    for (i = countries->begin(); i !=countries->end(); ++i) {
        cout << left << '|' << setw(20) << *(i->first)->name << '|' << setw(20) << *(i->first)->continent->name  << '|';
        vector<adjacency>::iterator t;
        for (t = (i->second).begin(); t !=(i->second).end(); ++t) {
            cout << left << setw(25) << *((t->first)->name) + ": " + ((t->second == 0) ? "land" : "water");
        }
        cout << endl;
    }
    cout << "-------------------------------------------------\n\n";
}

bool Map::isValid()
{
    cout << endl << "VALIDITY: " << endl;
    return  isConnected() && isContinentsConnected();
}

bool Map::isConnected()
{

    auto *visited = new vector<pair<Country*, bool>>;
    for (auto country : *(countries)) {
        visited->push_back(make_pair(country.first, false));
    }

    search((visited->begin())->first, visited, false);

    vector<pair<Country*, bool>>::iterator w;
    for (w = visited->begin(); w !=visited->end(); ++w) {

        if (!w->second)
        {
            cout << *(w->first->name) << " is not connected to any other region." << endl;
            cout << "Map countries are NOT CONNECTED. Invalid." << endl;
            delete visited;
            return false;
        }
    }

    cout << "Countries are connected." << endl;
    delete visited;
    return true;
}

void Map::search(Country* countrySearch, vector<pair<Country*, bool>> *visited, bool byContinent)
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

            vector<adjacency>::iterator w;
            for (w = (t->second).begin(); w !=(t->second).end(); ++w) {

                if (byContinent && (*((w->first)->continent->name) != *(countrySearch->continent->name))) {
                    continue;
                }

                vector<pair<Country*, bool>>::iterator q;
                for (q = visited->begin(); q !=visited->end(); ++q) {
                    if ((q->first) == w->first && (!q->second))
                    {
                        search(w->first, visited, byContinent);
                    }
                }

            }

        }
    }

}

bool Map::isContinentsConnected()
{
    for (auto continent : *(continents)) {
        auto *visited = new vector<pair<Country*, bool>>;
        for (auto country : (continent.second)) {
            visited->push_back(make_pair(country, false));
        }

        search((visited->begin())->first, visited, true);

        vector<pair<Country*, bool>>::iterator w;
        for (w = visited->begin(); w !=visited->end(); ++w) {

            if (!w->second)
            {
                cout << *(w->first->name) << " is not connected to any other region in its continent." << endl;
                cout << "Map continents are NOT CONNECTED. Invalid." << endl;
                delete visited;
                return false;
            }
        }
        delete visited;
    }

    cout << "Continents are connected." << endl;
    return true;
}