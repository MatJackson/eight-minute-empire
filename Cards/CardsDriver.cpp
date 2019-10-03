//
// Created by Tamar M on 2019-09-25.
//

#include <iostream>
#include <array>
#include "Cards.h"

using namespace std;

int main() {

    // init deck
    Deck deck = Deck();
    cout << "breakpoint here" << endl;

    // generate the cards
    deck.generateDeck();
    cout << "breakpoint here" << endl;

    // shuffle the deck
    deck.shuffle();
    cout << "breakpoint here" << endl;

    // draw initial hand

    // perform exchanges

    // ?edge cases

    return 0;
}