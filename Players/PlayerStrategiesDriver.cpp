//
// Created by Tamar M on 2019-11-09.
//
#include "PlayerStrategies.h"
#include "../Game/Game.h"
using namespace std;

int main() {

    Game* game = new Game();
    MapLoader* mapLoader = new MapLoader();
    game->map = mapLoader->map;
    game->deck = new Deck();
    game->deck->generateDeck();
    game->players = new vector<Player*>;

    //FIRST PLAYER - HUMAN
    Player* human = new Player(game->map, "Player1", 3, 10, 14);
    human->setStrategy(new HumanStrategy());
    game->players->push_back(human);
    game->startingPlayer = human;

    //SECOND PLAYER - GREEDY COMPUTER
    Player* greedy = new Player(game->map, "Player2", 3, 10, 14);
    greedy->setStrategy(new GreedyComputerStrategy());
    game->players->push_back(greedy);

    //THIRD PLAYER - MODERATE
    Player* moderate = new Player(game->map, "Player3", 3, 10, 14);
    moderate->setStrategy(new ModerateComputerStrategy());
    game->players->push_back(moderate);

    game->deck->shuffle();
    game->hand = new Hand(game->deck);
    game->hand->printHand();

    for (auto player : *(game->players)) {
        player->PlaceNewArmies(3, game->map->startingRegion, false);
    }

    game->mainGameLoop();

}