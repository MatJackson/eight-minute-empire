//
// Created by Tamar M on 2019-11-17.
//

#include "GameEngine.h"
#include <iostream>

using namespace std;

int main() {

    Game* game = new Game( );

    StateChange stateChange = StateChange(game);
    ScoreView scoreChange = ScoreView(game);

    //initialize map
    Map *map = Map::getInstance();

    auto *north = new Continent("North");

    auto *usa = new Country("USA", north);
    auto *can = new Country("Canada", north);

    map->addCountry(usa);
    map->addCountry(can);

    map->addAdjacency(usa, can, "L");

    //make players
    Player *player = new Player(map, "Player 1", 12, 13, 40);
    Player *player2 = new Player(map,"Player 2", 12, 13, 40);

    //initialize game
    game->map = map;
    game->players->push_back(player);
    game->players->push_back(player2);
    game->maxCardCount = new int(1);


    //change state
    game->changeState((""));

    //place armies to conquer canada and north america
    player->PlaceNewArmies(3, can, true);
    game->isConquered();

    //change state
    game->changeState("");

    //max card count
    Card *card = new Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_DESTROY_ARMY, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );
    player2->hand->push_back(card);

    game->changeState("");



}