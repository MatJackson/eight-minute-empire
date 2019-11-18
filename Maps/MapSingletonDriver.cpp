//
// Created by Tamar M on 2019-11-10.
//


#include <iostream>
#include "Map.h"

using namespace std;

int main() {

    Map* map1 = Map::getInstance();
    Map* map2 = Map::getInstance();

    cout << "Are both maps the same? ";

    string answer = "no!";
    if (map1 == map2) {
        answer = "Yes :)";
    }

    cout << answer;

    Continent* northAmerica = new Continent("North America");
    Country* canada = new Country("Canada", northAmerica);

    map1->addCountry(canada);

    cout << "\n\nMap 1: ";
    map1->display();

    cout << "\nMap 2: ";
    map2->display();

}