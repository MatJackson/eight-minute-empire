//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_CARDS_H
#define EIGHT_MINUTE_EMPIRE_CARDS_H

#include <vector>
#include <string>

using namespace std;

class Card {
public:
    string good;
    string action;
    Card(string g, string a) : good(g), action(a) { }
};

class Deck {
public:
    vector<Card*> deck;
    Deck(int deckSize);
    void draw();
};

class Hand {
public:
    typedef pair<Card*, double> handCard;
    vector<handCard> hand;
    Hand();
    void exchange();
};

#endif //EIGHT_MINUTE_EMPIRE_CARDS_H
