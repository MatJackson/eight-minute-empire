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
    Player* human = new Player(game->map, "Human", 3, 10, 14);
    human->setStrategy(new HumanStrategy());
    game->players->push_back(human);

    //SECOND PLAYER - GREEDY COMPUTER
    Player* greedy = new Player(game->map, "Greedy Computer", 3, 10, 14);
    greedy->setStrategy(new GreedyComputerStrategy());
    game->players->push_back(greedy);

    //THIRD PLAYER - MODERATE
    Player* moderate = new Player(game->map, "Moderate Computer", 3, 10, 14);
    moderate->setStrategy(new ModerateComputerStrategy());
    game->players->push_back(moderate);

    // initialize deck
    game->deck->shuffle();
    game->hand = new Hand(game->deck);
    game->hand->printHand();

    // initialize armies
    for (auto player : *(game->players)) {
        player->PlaceNewArmies(3, game->map->startingRegion, false);
    }

    // take 3 turns each
    for(int count = 0; count < 3; count++){

        game->takeTurn(human);
        human->display();

        game->takeTurn(greedy);
        greedy->display();

        game->takeTurn(moderate);
        moderate->display();
    }

    // strategy can be changed during the game
    greedy->setStrategy(new ModerateComputerStrategy);
    *(greedy->name) = "Greedy turned Moderate";

    // take another turn
    game->takeTurn(human);
    game->takeTurn(greedy);
    game->takeTurn(moderate);
}