//
// Created by Tamar M on 2019-10-29.
//

#include "Game.h"
#include <iostream>
#include <string>
#include <limits>

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
    hand = new Hand(deck);
    cout << "6 first open cards!" << endl;
    hand->printHand();

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

    // Player claims coin tokens and maxCardCount determined.
    int coinsPerPlayer = 0;
    switch(playerNum)
    {
        case 2:
            maxCardCount = new int(13);
            coinsPerPlayer = 14;
            break;
        case 3:
            maxCardCount = new int(10);
            coinsPerPlayer = 11;
            break;
        case 4:
            maxCardCount = new int(8);
            coinsPerPlayer = 9;
            break;
        case 5:
            maxCardCount = new int(7);
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
    startingPlayer = winner;
    cout << "Winner is: " << *(winner->name) << endl;
    cout << "State After Paying Bid:" << endl;
    printf("\t|%-10s|%-5s|%-5s|%-5s|\n", "Player", "Bid", "Coin", "Age");
    for (auto player : *players) {
        printf("\t|%-10s|%5d|%5d|%5d|\n", "Player", (*(player->bidding->getAmountBid())), *(player->tokens), *(player->age));
    }
    cout << endl;

    return 0;

}

void Game::takeTurn(Player *player) {
    Card *selectedCard = nullptr;
    int indexOfCardToExchange;

    // Select a card
    cout << "\n\n\n" << endl;
    printScoreCard();
    hand->printHand();
    cout << *player->name << ": Coins = " << *player->tokens << endl;
    player->printGoods();

    while (!selectedCard) {
        indexOfCardToExchange = player->pickCard(hand);
        selectedCard = hand->exchange(indexOfCardToExchange, player->tokens);
    }

    // Add the card to the player hand
    player->hand->push_back(selectedCard);

    // Display the selected card
    cout << endl;
    cout << "You have selectedCard:" << endl;
    selectedCard->printCard();

    // play the selected card
    player->display();
    playCard(*selectedCard, *player);
    cout << endl; // breakpoint line.
}

void Game::mainGameLoop() {
    int playerCount = players->size();
    int indexOfActivePlayer = 0;
    bool gameOver = false;

    // get index of starting player
    for (auto player : *players) {
        if (startingPlayer == player) {
            break;
        } else {
            indexOfActivePlayer++;
        }
    }

    while (!gameOver) {
        takeTurn(players->at(indexOfActivePlayer));

        indexOfActivePlayer = (indexOfActivePlayer + 1) % playerCount;
        gameOver = players->at(indexOfActivePlayer)->hand->size() == *maxCardCount;
    }
}

bool Game::playCard(Card& card, Player& player) {

    cout << "\nNEW CARD SELECTED! " << endl;
    card.printCard();

    if(card.combinationType==0) {
        playAction(card.actions[0], player);
    }
    else {
        AndOrAction(card.combinationType, card.actions, player);
    }

    return true;
}

bool Game::playAction(Action& action, Player& player) {

    int count = action.count;
    string countryName;
    int armiesNum = 0;
    string playerName;
    bool success;
    string choice;

    do {
        if (player.strategy->interaction()) {
            cout << "Write 'ignore' to skip or anything else to proceed. ";
            cin >> choice;
            if (choice == "ignore") {
                return player.Ignore();
            }
        }

        switch (action.type) {
            case 0 : {
                Country *country = nullptr;
                if (player.strategy->interaction()) {
                    while (!country) {
                        cout << "Name country to add armies in: ";
                        cin >> countryName;
                        country = map->findCountry(countryName);
                    }
                    while (true) {
                        cout << "\nHow many armies to add in country? ";
                        cin >> armiesNum;

                        if (cin.fail() || armiesNum > count || armiesNum <= 0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid number." << endl;
                        } else {
                            break;
                        }
                    }
                } else {
                    country = map->countries->front().first;
                    armiesNum = count;
                }
                    success = player.PlaceNewArmies(armiesNum, country, false);
                    if (success) {
                        count -= armiesNum;
                    }

            }
                break;
            case 1 : {
                Country *to = nullptr;
                Country *from = nullptr;
                if (player.strategy->interaction()) {
                    while (!from) {
                        cout << "Name country to move armies from: ";
                        cin >> countryName;
                        from = map->findCountry(countryName);
                    }
                    while (!to) {
                        cout << "Name country to move armies to: ";
                        cin >> countryName;
                        to = map->findCountry(countryName);
                    }
                    while (true) {
                        cout << "\nHow many armies to move? ";
                        cin >> armiesNum;

                        if (cin.fail() || armiesNum > count || armiesNum <= 0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid number." << endl;
                        } else {
                            break;
                        }
                    }
                } else {
                    for (auto countryFrom : *(player.armiesIn)) {
                        if (countryFrom.second > 0) {
                            from = countryFrom.first;
                            for (auto countryTo : *(map->countries)) {
                                if (countryTo.first == from) {
                                    to = (countryTo.second).front().first;
                                    if (countryFrom.second > count) {
                                        armiesNum = count;
                                    }
                                    else {
                                        armiesNum = countryFrom.second;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
                success = player.MoveOverLand(armiesNum, to, from);
                if (success) {
                    count -= armiesNum;
                }
            }
                break;
            case 2 : {
                Country *to = nullptr;
                Country *from = nullptr;
                if (player.strategy->interaction()) {
                    while (!from) {
                        cout << "Name country to move armies from: ";
                        cin >> countryName;
                        from = map->findCountry(countryName);
                    }
                    while (!to) {
                        cout << "Name country to move armies to: ";
                        cin >> countryName;
                        to = map->findCountry(countryName);
                    }
                    while (true) {
                        cout << "\nHow many armies to move? ";
                        cin >> armiesNum;

                        if (cin.fail() || armiesNum > count || armiesNum <= 0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid number." << endl;
                        } else {
                            break;
                        }
                    }
                } else {
                    for (auto countryFrom : *(player.armiesIn)) {
                        if (countryFrom.second > 0) {
                            from = countryFrom.first;
                            for (auto countryTo : *(map->countries)) {
                                if (countryTo.first == from) {
                                    to = (countryTo.second).front().first;
                                    if (countryFrom.second > count) {
                                        armiesNum = count;
                                    }
                                    else {
                                        armiesNum = countryFrom.second;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
                success = player.MoveOverLand(armiesNum, to, from);
                if (success) {
                    count -= armiesNum;
                }
            }
                break;
            case 3 : {
                Country *country = nullptr;
                if (player.strategy->interaction()) {
                    while (!country) {
                        cout << "Name country to build a city in: ";
                        cin >> countryName;
                        country = map->findCountry(countryName);
                    }
                } else {
                    for (auto countryToBuild : *(player.armiesIn)) {
                        if (countryToBuild.second > 0) {
                            country = countryToBuild.first;
                            break;
                        }
                    }
                }
                success = player.BuildCity(country);
                if (success) {
                    count -= 1;
                }
            }
                break;
            case 4 : {
                Player* playerToDestroy = nullptr;
                Country *country = nullptr;

                while(true) {
                    if (player.strategy->interaction()) {
                        while (!playerToDestroy) {
                            cout << "Name player of which you want to destroy an army: ";
                            cin >> playerName;
                            playerToDestroy = findPlayerByName(playerName);
                        }
                        while (!country) {
                            cout << "Name country to destroy an army of that player in: ";
                            cin >> countryName;
                            country = map->findCountry(countryName);
                        }
                    } else {
                        playerToDestroy = findPlayerByName("Player1");
                        for (auto countryToDestroy : *(playerToDestroy->armiesIn)) {
                            if (countryToDestroy.second > 0) {
                                country = countryToDestroy.first;
                                break;
                            }
                        }
                    }
                    if (player.DestroyArmy(country, playerToDestroy)) {
                        count -= 1;
                        break;
                    }

                }
                cout << endl;
            }
                break;
        }

        if (count>0) {
            cout << endl << "You still have " << count << " left... ";
        }

    } while(count>0);

    return true;
}

bool Game::AndOrAction(Card::CombinationType type, vector<Action> actions, Player& player) {


    if (player.strategy->interaction()) {
        cout << "What action would you like to do" << ((type == 2) ? " first?" : "?")
             << " Select by typing the index of the actions (1 or 2).";

        int index;
        while (true) {
            cin >> index;

            if (cin.fail() || index > 2 || index < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid number." << endl;
            } else {
                break;
            }
        }
        playAction(actions[index - 1], player);
        if (type == 1) {
            return true;
        }
        actions.erase(actions.begin() + (index - 1));

        cout << "Next action: " << (actions.begin()->getName()) << endl;
        playAction(actions[0], player);
    } else {
        Action action = actions[0];
        for(int c = 0; c < 2; c++) {
            if (actions[c].type == 3 || actions[c].type == 4) {
                action = actions[c];
            }
        }
        playAction(action, player);
    }

    return true;
}

Player* Game::findPlayerByName(string playerName) {
    vector<Player*>::iterator p;
    for (p = (players)->begin(); p !=(players)->end(); ++p) {
        if (*((*p)->name) == playerName) {
            return *p;
        }
    }

    return nullptr;
}

void Game::printScoreCard() {
    cout << "Good Score Card: required good count to achieve given scores" << endl;
    printf("\t|%-15s|%-10s|%-10s|%-10s|%-10s|\n", "Good Type", "Score: 1", "Score: 2", "Score: 3", "Score: 6");
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Ruby", 1, 2, 3, 4);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Ore", 2, 3, 4, 5);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Wood", 2, 4, 5, 6);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Anvil", 2, 4, 6, 7);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Carrot", 3, 5, 7, 8);

}

void Game::computeScore() {

    for (auto continent : *map->continents) {
        vector<int> continentControlCount(players->size());
        Player *continentOwner = nullptr;

        for (auto country : continent.second) {
            Player *countryOwner = nullptr;
            int highestControlCount = 0;

            for (auto player : *players) {
                int playerControlCount = player->getArmiesInCountry(country)->second + player->getCitiesInCountry(country)->second;

                if (playerControlCount > highestControlCount) {
                    highestControlCount = playerControlCount;
                    countryOwner = player;
                } else if (playerControlCount == highestControlCount) {
                    countryOwner = nullptr;
                }
            }

            if (countryOwner != nullptr) {
                (*countryOwner->score->regionScore)++;

                int playerIndex = 0;
                for (auto player : *players) {
                    if (countryOwner == player) {
                        continentControlCount.at(playerIndex)++;
                    }
                    playerIndex++;
                }
            }

        }

        int highestContinentControlCount = 0;
        for (int i = 0; i < continentControlCount.size(); i++) {
            if (continentControlCount.at(i) > highestContinentControlCount) {
                highestContinentControlCount = continentControlCount.at(i);
                continentOwner = players->at(i);
            } else if (continentControlCount.at(i) == highestContinentControlCount) {
                continentOwner = nullptr;
            }
        }

        if (continentOwner != nullptr) {
            (*continentOwner->score->continentScore)++;
        }
    }

    printScoreCard();
    cout << "\n\n\nFinal Spread of goods:" << endl;
    for (auto player : *players) {
        cout << *(player->name) << ":" << endl;
        player->printGoods();
    }

    for (auto player : *players) {
        player->computeTotalGoodScore();
        cout << endl;
    }

    printScores();

    cout << "\n\nWinner Is:" << endl;

    int highestScore = 0;

    for (auto player : *players) {
        if (player->score->getTotalScore() > highestScore) {
            highestScore = player->score->getTotalScore();
        }
    }

    vector<Player> winners;
    for (auto player : *players) {
        if (player->score->getTotalScore() == highestScore) {
            winners.push_back(*player);
        }
    }

    for (auto winner : winners) {
        cout << *(winner.name) << endl;
    }
}

void Game::printScores() {

    printf("\t|%-15s|%-10s|%-10s|%-10s|%-10s|\n", "Player", "Continent", "Region", "Goods", "Total");
    int playerNumber = 1;
    for (auto player : *players) {
        printf("\t|%-6s%-9d|%10d|%10d|%10d|%10d|\n", "player", playerNumber,
                *player->score->continentScore,
                *player->score->regionScore,
                *player->score->goodScore,
                player->score->getTotalScore()
        );
        playerNumber++;
    }

}