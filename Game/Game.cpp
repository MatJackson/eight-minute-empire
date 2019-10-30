//
// Created by Tamar M on 2019-10-29.
//

#include "Game.h"
#include <iostream>
#include <string>

int playerNum;

Game::Game()
{

}

void Game::initialize()
{
    //initialize map
    MapLoader* mapLoader = new MapLoader();
    map = mapLoader->map;

    //initialize deck
    deck = new Deck();
    deck->generateDeck();

    //initialize players
    players = new vector<Player*>;

    while (true) {
        cout << "How many players would like to play? ";
        cin >> playerNum;

        if (cin.fail() || playerNum < 2 || playerNum > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid player number. There can only be 2 to 5 players in the game. " << endl;
        } else {

            for(int i = 1; i <= playerNum; i++) {
                Player* player = new Player(map, "Player" + to_string(i), 3, 0, 14);
                players->push_back(player);
                cout << "Created player " + *(player->name);
                int age;
                while (true) {
                    cout << ". How old are you? ";
                    cin >> age;

                    if (cin.fail() || age < 1) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid age. " << endl;
                    } else {
                        (*(player->age))=age;
                        break;
                    }
                }
            }
            cout << endl;
            break;
        }
    }



}

void Game::startup()
{
    //shuffle deck
    deck->shuffle();

    //generate open cards and display
    Hand hand = Hand(deck);
    cout << "6 first open cards!" << endl;
    hand.printHand();

    //place armies at starting point
    cout << "\nPlace 3 armies on the starting region of the board! (" << *(map->startingRegion->name) << ")" << endl;
    for (auto player : *players) {
        player->PlaceNewArmies(3, map->startingRegion);
}

    //IMPLEMENT TURN
    //!!!!!!!!!!!!!!!!!!!!!!!!

    //player claims coin tokens
    int coinsPerPlayer = 0;
    switch(playerNum)
    {
        case 2:
            coinsPerPlayer = 14;
            break;
        case 3:
            coinsPerPlayer = 11;
            break;
        case 4:
            coinsPerPlayer = 9;
            break;
        case 5:
            coinsPerPlayer = 8;
            break;
    }
    cout << endl << "Each player is given " << coinsPerPlayer << " coins.\n" << endl;
    for (auto player : *players) {
        player->setTokens(coinsPerPlayer);
    }

    //players bid
    for (auto player : *players) {
        *(player->bidding->playerAge)=*(player->age);
        *(player->bidding->availableCoin)=*(player->tokens);
        cout << *(player->name) << ": " << endl;
        player->bidding->bid();
    }

    // get winner
    Player* winner;
    BiddingFacility *winningBidder = nullptr;
    for (auto player : *players) {
        if (player->bidding->largerBidThan(winningBidder)) {
            winner = player;
            winningBidder = player->bidding;
        }
    }
    winningBidder->payBid();
    cout << "Winner is: " << *(winner->name) << endl;
    cout << "State After Paying Bid:" << endl;
    printf("\t|%-10s|%-5s|%-5s|%-5s|\n", "Player", "Bid", "Coin", "Age");
    for (auto player : *players) {
        printf("\t|%-10s|%5d|%5d|%5d|\n", "Player", (*(player->bidding->getAmountBid())), *(player->tokens), *(player->age));
    }
    cout << endl;

}