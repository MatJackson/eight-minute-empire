//
// Created by Tamar M on 2019-10-29.
//

#ifndef EIGHT_MINUTE_EMPIRE_GAME_H
#define EIGHT_MINUTE_EMPIRE_GAME_H

#include "../Maps/Map.h"
#include "../Maps/MapLoader.h"
#include "../Players/Player.h"
#include "GameObservers.h"

using namespace std;

class Game : public Subject { //concrete subject
public:
    vector<Player*> *players;
    Map* map;
    Deck* deck;
    Player* non_player; //optional - only if 2 players in the game
    Player* activePlayer;
    Card *selectedCard;
    Hand* hand;
    int *maxCardCount;
    string state;

    Game();
    void changeState(string stateChange);
    int initialize();
    int startup();
    void takeTurn(Player* player);
    void mainGameLoop();
    bool playCard(Card& card, Player& player);
    bool playAction(Action& action, Player& player);
    bool AndOrAction(Card::CombinationType type, vector<Action> actions, Player& player);
    Player* findPlayerByName(string playerName);
    void printScoreCard();
    void computeScore();
    void printScores();
};

class StateChange : public Observer { //concrete observer
public:
    StateChange();
    StateChange(Game* s);
    void Update();
    void display();
private:
    Game *subject;
};


#endif //EIGHT_MINUTE_EMPIRE_GAME_H
