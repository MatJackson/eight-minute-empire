//
// Created by Tamar M on 2019-09-20.
//

#include <algorithm>
#include "Map.h"
#include <iostream>
#include <list>

using namespace std;

Map::Map()
{
    countries = new vector<country>;
    continents = new vector<continent>;
}

void Map::addCountry(Country *country)
{
    vector<Country*> init = vector<Country*>();
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

    //cout << "Added adjacency between " << *(to->name) << " and " << *(from->name)<< " to the map." << endl;
    return true;
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
    cout << "Continents: " << endl;
    vector<continent>::iterator w;
    for (w = continents->begin(); w !=continents->end(); ++w) {
        cout << *(w->first)->name << endl;
        cout << "    Countries: ";
        vector<Country*>::iterator t;
        for (t = (w->second).begin(); t !=(w->second).end(); ++t) {
            cout << " " << *((*t)->name);
        }
        cout << endl << endl;
    }
    cout << endl << "-------------------------------------------------" << endl;
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

            vector<Country*>::iterator w;
            for (w = (t->second).begin(); w !=(t->second).end(); ++w) {

                if (byContinent && (*((*w)->continent->name) != *(countrySearch->continent->name))) {
                    continue;
                }

                vector<pair<Country*, bool>>::iterator q;
                for (q = visited->begin(); q !=visited->end(); ++q) {
                    if ((q->first) == *w && (!q->second))
                    {
                        search(*w, visited, byContinent);
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