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

int Game::initialize()
{
    //initialize map
    MapLoader* mapLoader = new MapLoader();
    map = mapLoader->map;
    if(!map) {
        return 0;
    }

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

    if(players->size()==2) {
        non_player = new Player(map, "Player3", 3, 0, 4);
    }
    else {
        non_player= nullptr;
    }

    return 0;

}

int Game::startup()
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
        player->PlaceNewArmies(3, map->startingRegion, false);
}

    //If 2 players, place armies of 3rd non-player
    if(players->size()==2) {
        cout << "\nSince there are only 2 players, each player "
                "takes turns placing one army at a time of a third, non-player in any region on the "
                "board until ten armies have been placed!" << endl;
        for (int c = 0; c < 10 ; c++) {
            int turn = c%2;
            string countryName;
            Country *country = nullptr;
            while (!country) {
                cout << "Your turn, " << *((*players)[turn]->name) << ". Which country would you like to add one army for Player3? ";
                cin >> countryName;
                country = map->findCountry(countryName);
            }
            non_player->PlaceNewArmies(1, country, true);
        }
    }

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
    cout << endl << "Here are the initial states of each player" << endl;
    for (auto player : *players) {
        player->setTokens(coinsPerPlayer);
        player->display();
    }

    //players bid
    cout << "\n\n----------- BIDDING ------------------------\n";
    cout << "Players must bid to decide who starts first. The biding consists of each player"
            "picking up his coins and privately chooses a number to bid. When all players are ready, all players"
            "reveal the amount they have chosen to bid at the same time.\nThe player who bids the most coins"
            "wins the bid and puts the coins he bid in the supply. Other players do not pay coins if they lost"
            "the bid. If the bids are tied for most, the youngest player wins the bid and pays his coins.\nIf all"
            "bids are zero, the youngest player wins the bid.\n\n";

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

    return 0;

}