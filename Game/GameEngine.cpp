//
// Created by Tamar M on 2019-10-29.
//

#include "GameEngine.h"
#include <iostream>
#include <string>
#include <limits>

int playerNum;

StateChange::StateChange() {

};

StateChange::StateChange(GameEngine* s) {
    subject = s;
    subject->Attach(this);
};

void StateChange::Update() {
    display();
};
void StateChange::display() {
    if (subject->state == "start turn") {
        cout << "\n\n\n" << endl;
        cout << "------------------------ " << *(subject->activePlayer->name) << "'s turn! ------------------------\n" << endl;

        // Select a card
        //subject->printScoreCard();
        subject->hand->printHand();
        cout << *subject->activePlayer->name << ": Coins = " << *subject->activePlayer->tokens << endl;
        subject->activePlayer->printGoods();
    }

    if (subject->state == "select card") {
        cout << endl;
        cout << "You have selected Card:" << endl;
        subject->selectedCard->printCard();
    }

    if (subject->state == "play card") {
        subject->activePlayer->display();
    }
};

ScoreView::ScoreView() {

};

ScoreView::ScoreView(GameEngine* s) {
    subject = s;
    subject->Attach(this);
};

void ScoreView::Update() {
    display();
};
void ScoreView::display() {

    cout << "\n\n------------------------ PLAYERS ------------------------\n" << endl;
    for (auto player : *subject->players) {
        player->display();
        player->printGoods();
        if(player->hand->size() == *(subject->maxCardCount)) {
            cout << "\nCONGRATS!!! YOU HAVE THE MAX CARD COUNT!!!!\n";
        }
    }
    cout << "----------------------------------------------------------\n" << endl;

    cout << "\n\n------------------------ CONQUERINGS ------------------------\n" << endl;
    for (auto continentConquered : *subject->continentsConquered) {
        cout << *(continentConquered.second->name) << " has conquered the CONTINENT " << *(continentConquered.first->name) << endl;
    }
    for (auto countryConquered : *subject->countriesConquered) {
        cout << *(countryConquered.second->name) << " has conquered " << *(countryConquered.first->name) << endl;
    }
    cout << "--------------------------------------------------------\n" << endl;
};

// GAME

GameEngine::GameEngine() {
    players = new vector<Player*>;
    countriesConquered = new vector<pair<Country*, Player*>>;
    continentsConquered = new vector<pair<Continent*, Player*>>;
}

void GameEngine::changeState(string change) {
    state = change;
    Notify();
}

int GameEngine::initialize()
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

    while (true) {
        cout << "How many players would like to play? ";
        cin >> playerNum;

        if (cin.fail() || playerNum < 2 || playerNum > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid player number. There can only be 2 to 4 players in the game. " << endl;
        } else { break; }
    }

    int mode;

    for(int i = 1; i <= playerNum; i++) {

        mode = 0;

        while (true) {
            cout << "\nChoose mode for Player" << playerNum << ": (0 for human players, 1 for greedy computer player or 2 for moderate computer player): ";
            cin >> mode;

            if (cin.fail() || mode < 0 || mode > 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid number. " << endl;
            } else {
                break; }
        }

        Player* player = new Player(map, "Player" + to_string(i), 3, 0, 14);
        if(mode==1){
            player->setStrategy(new GreedyComputerStrategy);
        }
        if(mode==2){
            player->setStrategy(new ModerateComputerStrategy);
        }
        players->push_back(player);
        cout << "Created player " + *(player->name);
        *(player->age) = player->strategy->submitAge();
    }
    cout << endl;

    non_player= nullptr;

    return 0;

}

int GameEngine::startup()
{
    //shuffle deck
    deck->shuffle();

    //generate open cards and display
    hand = new Hand(deck);

    //place armies at starting point
    cout << "\nPlace 3 armies on the starting region of the board! (" << *(map->startingRegion->name) << ")" << endl;
    for (auto player : *players) {
        player->PlaceNewArmies(3, map->startingRegion, true);
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

    bool bid = false;
    for (auto player : *players) {
        if(player->strategy->interaction()) {
            bid = true;
        }
    }

    Player* winner = *(players->begin());

    if (bid) {
        for (auto player : *players) {
            *(player->bidding->playerAge)=*(player->age);
            *(player->bidding->availableCoin)=*(player->tokens);
            cout << *(player->name) << ": " << endl;
            player->bidding->bid();
        }
        // get winner
        BiddingFacility *winningBidder = nullptr;
        for (auto player : *players) {
            if (player->bidding->largerBidThan(winningBidder)) {
                winner = player;
                winningBidder = player->bidding;
            }
        }
        winningBidder->payBid();
    }


    activePlayer = winner;
    cout << "Winner is: " << *(winner->name) << endl;
    cout << "State After Paying Bid:" << endl;
    printf("\t|%-10s|%-5s|%-5s|%-5s|\n", "Player", "Bid", "Coin", "Age");
    for (auto player : *players) {
        printf("\t|%-10s|%5d|%5d|%5d|\n", "Player", (*(player->bidding->getAmountBid())), *(player->tokens), *(player->age));
    }
    cout << endl;

    return 0;

}

void GameEngine::takeTurn(Player *player) {
    selectedCard = nullptr;
    int indexOfCardToExchange;

    changeState("start turn");

    while (!selectedCard) {
        indexOfCardToExchange = player->pickCard(hand);
        selectedCard = hand->exchange(indexOfCardToExchange, player->tokens);
    }

    // Add the card to the player hand
    player->hand->push_back(selectedCard);

    changeState("select card");
    changeState("select card");

    changeState("play card");

    playCard(*selectedCard, *player);
    cout << endl; // breakpoint line.

    changeState("post turn");
}

void GameEngine::mainGameLoop() {
    int playerCount = players->size();
    int indexOfActivePlayer = 0;
    bool gameOver = false;

    // get index of starting player
    for (auto player : *players) {
        if (activePlayer == player) {
            break;
        } else {
            indexOfActivePlayer++;
        }
    }

    while (!gameOver) {
        activePlayer = players->at(indexOfActivePlayer);
        takeTurn(activePlayer);
        isConquered();

        indexOfActivePlayer = (indexOfActivePlayer + 1) % playerCount;
        gameOver = players->at(indexOfActivePlayer)->hand->size() == *maxCardCount;
    }
}

bool GameEngine::playCard(Card& card, Player& player) {

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

bool GameEngine::playAction(Action& action, Player& player) {

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
                        playerToDestroy = players->front();
                        if (playerToDestroy->name == player.name) {
                            playerToDestroy = players->at(1);
                        }
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

        if (count>0 && player.strategy->interaction()) {
            cout << endl << "You still have " << count << " left... ";
        }

    } while(count>0 && player.strategy->interaction());

    return true;
}

bool GameEngine::AndOrAction(Card::CombinationType type, vector<Action> actions, Player& player) {


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

Player* GameEngine::findPlayerByName(string playerName) {
    vector<Player*>::iterator p;
    for (p = (players)->begin(); p !=(players)->end(); ++p) {
        if (*((*p)->name) == playerName) {
            return *p;
        }
    }

    return nullptr;
}

void GameEngine::printScoreCard() {
    cout << "Good Score Card: required good count to achieve given scores" << endl;
    printf("\t|%-15s|%-10s|%-10s|%-10s|%-10s|\n", "Good Type", "Score: 1", "Score: 2", "Score: 3", "Score: 6");
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Ruby", 1, 2, 3, 4);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Ore", 2, 3, 4, 5);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Wood", 2, 4, 5, 6);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Anvil", 2, 4, 6, 7);
    printf("\t|%-15s|%10d|%10d|%10d|%10d|\n", "Carrot", 3, 5, 7, 8);

}

void GameEngine::displayScores() {

    //printScoreCard();

    printf("\t|%-15s|%-10s|%-10s|%-10s|%-10s|\n", "Player", "Coins", "Cards", "Goods", "Victory");
    int playerNumber = 1;
    for (auto player : *players) {
        printf("\t|%-6s%-9d|%10d|%10d|%10d|%10d|\n", "player", playerNumber,
               *player->tokens,
               player->hand->size(),
               *player->score->goodScore,
               player->getTotalScore()
        );
        playerNumber++;
    }
}

void GameEngine::computeWinner() {

    isConquered();

    for (auto player : *players) {
        player->computeTotalGoodScore();
        cout << endl;
    }

    int highestScore = 0;

    for (auto player : *players) {
        if (player->getTotalScore() > highestScore) {
            highestScore = player->getTotalScore();
        }
    }

    displayScores();

    vector<Player> winners;
    for (auto player : *players) {
        if (player->getTotalScore() == highestScore) {
            winners.push_back(*player);
        }
    }

    cout << "\n\nWinner Is:" << endl;
    for (auto winner : winners) {
        cout << *(winner.name) << endl;
    }
}

void GameEngine::isConquered() {

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

                //COUNTRY CONQUERED
                conquerCountry(*countryOwner, *country);

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
            conquerContinent(*continentOwner, *(continent.first));
        }
    }

}

void GameEngine::conquerContinent(Player& player, Continent& continent) {
    *(player.score->continentScore)+=1;
    bool alreadyConquered = false;
    for (auto continentConquered : *continentsConquered) {
        if (continentConquered.first->name == continent.name) {
            continentConquered.second = &player;
            alreadyConquered = true;
        }
    }
    if (!alreadyConquered) {
        continentsConquered->push_back(make_pair(&continent, &player));
    }
}

void GameEngine::conquerCountry(Player& player, Country& country) {
    *(player.score->regionScore)+=1;
    bool alreadyConquered = false;
    for (auto countryConquered : *countriesConquered) {
        if (countryConquered.first->name == country.name) {
            countryConquered.second = &player;
            alreadyConquered = true;
        }
    }
    if (!alreadyConquered) {
        countriesConquered->push_back(make_pair(&country, &player));
    }
}