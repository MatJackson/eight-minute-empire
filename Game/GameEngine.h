//
// Created by Tamar M on 2019-10-29.
//

#ifndef EIGHT_MINUTE_EMPIRE_GAMEENGINE_H
#define EIGHT_MINUTE_EMPIRE_GAMEENGINE_H

#include "../Maps/Map.h"
#include "../Maps/MapLoader.h"
#include "../Players/Player.h"
#include "GameObservers.h"

using namespace std;

class GameEngine : public Subject { //concrete subject
public:
    vector<Player*> *players;
    Map* map;
    Deck* deck;
    Player* non_player; //optional - only if 2 players in the game
    Player* activePlayer;
    Card *selectedCard;
    vector<pair<Continent*, Player*>> *continentsConquered;
    vector<pair<Country*, Player*>> *countriesConquered;
    Hand* hand;
    int *maxCardCount;
    string state;

    GameEngine();
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
    void displayScores();
    void computeWinner();
    void isConquered();
    void conquerContinent(Player& player, Continent& continent);
    void conquerCountry(Player& player, Country& country);
};

class StateChange : public Observer { //concrete observer
public:
    StateChange();
    StateChange(GameEngine* s);
    void Update();
    void display();
private:
    GameEngine *subject;
};

class ScoreView : public Observer { //concrete observer
public:
    ScoreView();
    ScoreView(GameEngine* s);
    void Update();
    void display();
private:
    GameEngine *subject;
};


#endif //EIGHT_MINUTE_EMPIRE_GAMEENGINE_H
