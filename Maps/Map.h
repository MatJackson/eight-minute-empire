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
        name = new string(n);
    }
};

struct Country {
    string *name;
    Continent *continent;
    Country(string n, Continent *c) {
        name = new string(n);
        continent = c;
    }
};

class Map {
private:
    typedef pair<Country*, Country*> adjacent;
    vector<Country*> *countries;
    vector<Continent*> *continents;
    vector<adjacent> *adjacencies;

public:
    Map();
    void addCountry(Country *country);
    bool addAdjacency(Country *from, Country *to);
    bool isAdjacent(Country *from, Country *to);
    Country* findCountry(string country);
    void display();
    bool isValid();
    bool isConnected();
    bool isContinentsConnected();
    bool isCountryOneContinent();
    vector<Country*> getCountries();
    vector<adjacent> getAdjacencies();

};

#endif //EIGHT_MINUTE_EMPIRE_MAP_H
