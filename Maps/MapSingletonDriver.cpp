//
// Created by Tamar M on 2019-11-10.
//


#include <iostream>
#include "Map.h"
#include "../Players/Player.h"

using namespace std;

int main() {

    Map* map = Map::getInstance();
    Map* map2 = Map::getInstance();

    cout << "Are both maps the same? ";

    string answer = "no!";
    if (map == map2) {
        answer = "Yes :)";
    }

    cout << answer;

}