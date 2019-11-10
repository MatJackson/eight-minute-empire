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
public:
    static Map* mapInstance;
    typedef pair<Country*, bool> adjacency;
    typedef pair<Country*, vector<adjacency>> country;
    typedef pair<Continent*, vector<Country*>> continent;
    vector<country> *countries;
    vector<continent> *continents;
    Country* startingRegion;

    Map();
    static Map* getInstance();
    void addCountry(Country *country);
    bool addAdjacency(Country *from, Country *to, bool type);
    int isAdjacent(Country *from, Country *to);
    Country* findCountry(string country);
    void display();
    bool isValid();
    bool isConnected();
    bool isContinentsConnected();
    void search(Country* country, vector<pair<Country*, bool>> *visited, bool byContinent);

};

#endif //EIGHT_MINUTE_EMPIRE_MAP_H