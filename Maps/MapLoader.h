//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_MAPLOADER_H
#define EIGHT_MINUTE_EMPIRE_MAPLOADER_H

#include "Map.h"

using namespace std;

class MapLoader {
public:
    Map *map;
    MapLoader();
    Map* useFile(string fileName);
    Map* load();
};

#endif //EIGHT_MINUTE_EMPIRE_MAPLOADER_H
