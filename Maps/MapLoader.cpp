//
// Created by Tamar M on 2019-09-25.
//

#include "MapLoader.h"
#include <fstream>
#include <iostream>

using namespace std;

MapLoader::MapLoader()
{
    map = load();
}

Map* MapLoader::useFile(string fileName)
{
    ifstream infile;
    infile.open(fileName);

    Map *map = new Map();

    string line;
    bool countries = false;
    bool adjacencies = false;
    while (getline(infile, line))
    {
        if(line=="") {
            continue;
        }
        if(line=="[Countries]") {
            countries=true;
            continue;
        }
        if(line=="[Adjacencies]") {
            adjacencies=true;
            countries=false;
            continue;
        }
        if(countries||adjacencies) {
            string delimiter = ",";
            string first = line.substr(0, line.find(delimiter));
            string second = line.substr(line.find(delimiter) + 1, line.length());
            if(first==line) {
                cout << "Must delimit elements by a comma." << endl;
                return nullptr;
            }
            if (countries) {
                try {
                    Continent *continent = new Continent(second);
                    Country *country = new Country(first, continent);
                    map->addCountry(country);
                } catch (const exception& e) {
                    cout << "Invalid country format" << endl;
                }
            }
            if (adjacencies) {
                try {
                    bool found = map->addAdjacency(map->findCountry(first), map->findCountry(second));
                    if(!found) {
                        cout << "Country listed in Adjacency list not found." << endl;
                        return nullptr;
                    }
                } catch (const exception& e) {
                    cout << "Invalid adjacency format" << endl;
                }
            }
            }
        }
    if(adjacencies==false){
        cout << "Invalid map. Map must be connected & each country should belong to only one continent!" << endl;
        return nullptr;
    }
    if (map->isValid()) {
        return map;
    } else {
        return nullptr;
    }

}

Map* MapLoader::load()
{
    Map* tryMap;
    do {
        cout << "Enter map file name: ";
        string fileName;
        cin >> fileName;
        tryMap = useFile("../Resources/" + fileName);
    } while (tryMap == nullptr);

    tryMap->display();

    return tryMap;
}

