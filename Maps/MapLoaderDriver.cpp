#include "Map.h"
#include "MapLoader.h"
#include <iostream>

using namespace std;

int main() {
    MapLoader *loader = new MapLoader("../Resources/world.map");
    if(loader->map== nullptr) {
        cout << "Invalid map";
    } else {
        loader->map->display();
    }
}
