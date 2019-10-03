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
};

struct Good {
    enum GoodType {
        RUBY,
        WOOD,
        CARROT,
        IRON,
        COAL,
        WILD
    };

    GoodType type;
    int count;

    Good() = default;
    Good(GoodType type, int count);
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
};

class Deck {
public:
//    Card *topCard;
    array<Card, 42> cards;
//    Deck();
//    Deck(int deckSize);
    void generateDeck(bool greaterThanFive);
//    void shuffle();
//    void draw();
};

class Hand {
public:
    array<Card, 5> cards;
    Hand();
    void exchange();
};

#endif //EIGHT_MINUTE_EMPIRE_CARDS_H
