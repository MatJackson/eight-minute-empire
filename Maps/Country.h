//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_COUNTRY_H
#define EIGHT_MINUTE_EMPIRE_COUNTRY_H

#include <vector>
#include <string>

using namespace std;

class Country {
public:
    string name;
    string continent; //should continents be their own class?
    string owned_by; //change to Player class
    int armies;
    Country(string n, string c) : name(n), continent(c) { }
    string displayCountry();
};

#endif //EIGHT_MINUTE_EMPIRE_COUNTRY_H
