//
// Created by Tamar M on 2019-09-20.
//
#ifndef EIGHT_MINUTE_EMPIRE_MAP_H
#define EIGHT_MINUTE_EMPIRE_MAP_H

#include <vector>
#include <string>

using namespace std;

struct Continent {
    string *name;
    Continent(string n) {
        name=&n;
    }
};

struct Country {
    string *name;
    Continent *continent;
    int *armies = 0;
    Country(string n, Continent &c) {
        name=&n;
        continent=&c;
    }
};

class Map {

public:
    typedef pair<Country*, Country*> adjacent;

    vector<Country*> *countries;
    vector<adjacent> *adjacencies;

    Map();
    void addCountry(Country &country);
    bool addAdjacency(Country &from, Country &to);
    bool isValid();
    bool isConnected();
    bool isContinentsConnected();
    bool isCountryOneContinent();

};

#endif //EIGHT_MINUTE_EMPIRE_MAP_H
