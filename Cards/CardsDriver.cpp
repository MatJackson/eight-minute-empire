//
// Created by Tamar M on 2019-09-25.
//

#include <iostream>
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
    Hand hand = Hand(&deck);
    cout << "breakpoint here" << endl;

    // perform exchanges
    int index = 0;
    while(index > -1) {
        cout << "Enter the index of a card: ";
        cin >> index;
        hand.exchange(index, 10);
        cout << "breakpoint here" << endl;
    }

    return 0;
}