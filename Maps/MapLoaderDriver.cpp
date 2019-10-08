#include "Map.h"
#include "MapLoader.h"
#include <iostream>

using namespace std;

int main() {

    MapLoader *loader;

   // do {
        cout << "Enter map file name: ";
        string fileName;
        //cin >> fileName;
        loader = new MapLoader("../Resources/world-valid.map");
    //} while (loader->map== nullptr);
}
