#include <iostream>
#include "../Maps/Map.h"
#include "Player.h"

using namespace std;

int main() {
    Map *map = Map::getInstance();

    auto *north = new Continent("North");

    auto *usa = new Country("USA", north);
    auto *can = new Country("Canada", north);

    map->addCountry(usa);
    map->addCountry(can);

    map->addAdjacency(usa, can);

    Player *player = new Player(map, "Player 1", 12, 13, 40);
    Player *player2 = new Player(map,"Player 2", 12, 13, 40);

    player->display();

    player->BuildCity(usa);
    player->display();

    player->PlaceNewArmies(80, usa, false);
    player->display();

    player2->PlaceNewArmies(9, usa, false);
    player2->display();

    player->MoveOverLand(6, usa, can);
    player->display();

    player->MoveArmies(1, usa, can);
    player->display();

    player->PayCoin(60);
    player->PayCoin(2);
    player->display();

    player->DestroyArmy(usa, player2);
    player2->display();

    player->PlaceNewArmies(1, usa, false);
    player->DestroyArmy(usa, player2);
    player2->display();

}