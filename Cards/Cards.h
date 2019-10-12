//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_CARDS_H
#define EIGHT_MINUTE_EMPIRE_CARDS_H

#include <array>
#include <string>
#include <vector>

using namespace std;

struct Action {
    static const char * const actions[];

    enum ActionType {
        ACTION_ADD_ARMY,
        ACTION_MOVE_OVER_LAND,
        ACTION_MOVE_OVER_LAND_OR_WATER,
        ACTION_BUILD_CITY,
        ACTION_DESTROY_ARMY
    };

    ActionType type;
    int count;

    Action() = default;
    Action(ActionType type, int count);
    string getName();
};

struct Good {
    static const char * const goods[];

    enum GoodType {
        GOOD_RUBY,
        GOOD_WOOD,
        GOOD_CARROT,
        GOOD_ANVIL,
        GOOD_ORE,
        GOOD_WILD
    };

    GoodType type;
    int count;

    Good() = default;
    Good(GoodType type, int count);
    string getName();
};

class Card {
public:
    enum CombinationType {
        SINGLE,
        OR,
        AND
    };

    Good good;
    CombinationType combinationType;
    vector<Action> actions;

    Card() = default;
    Card(Good good, Action action);
    Card(Good good, CombinationType combinationType, Action primaryAction, Action secondaryAction);
    string getCombinationType();
    void printCard();
};

class Deck {
public:
    Card *topCard;
    array<Card, 42> cards;
    void generateDeck();
    Deck();
    void shuffle();
    Card* draw();
    void printDeck();
};

class Hand {
public:
    Deck *deck;
    array<Card *, 6> cards;
    explicit Hand(Deck *deck);
    Card* exchange(int cardIndex, int coins);
    int cardCost(int cardIndex);
    void printHand();
private:
    void shiftCards(int index);

};

#endif //EIGHT_MINUTE_EMPIRE_CARDS_H
