//
// Created by Tamar M on 2019-09-20.
//
#ifndef EIGHT_MINUTE_EMPIRE_MAP_H
#define EIGHT_MINUTE_EMPIRE_MAP_H

#include <vector>
#include <string>
#include "../Players/Player.h"

using namespace std;

struct Continent {
public:
    string name;
    Continent(string n) : name(n) { }
};

struct Country {
public:
    string name;
    Continent continent;
    Player owned_by;
    int armies;
    Country(string n, string c) : name(n), continent(c) { }
};

class Map {

public:
    typedef pair<Country*, Country*> adjacent;
    vector<Country*> countries;
    vector<adjacent> adjacencies;

    Map();
    void addCountry(const string& name, const string& continent);
    bool addAdjacency(const string& from, const string& to);
    bool isValid();
    bool isConnected();
    bool isContinentsConnected();
    bool isCountryOneContinent();

};

#endif //EIGHT_MINUTE_EMPIRE_MAP_H
