//
// Created by Tamar M on 2019-09-20.
//
#ifndef EIGHT_MINUTE_EMPIRE_MAP_H
#define EIGHT_MINUTE_EMPIRE_MAP_H

#include <vector>
#include <string>
#include "Country.h"

using namespace std;

class Map {

public:
    typedef pair<Country*, Country*> adjacent;
    vector<Country*> countries;
    vector<adjacent> adjacencies;

    Map();
    void addCountry(const string& name, const string& continent);
    void addAdjacency(const string& from, const string& to);
    bool isConnected();
};

#endif //EIGHT_MINUTE_EMPIRE_MAP_H
