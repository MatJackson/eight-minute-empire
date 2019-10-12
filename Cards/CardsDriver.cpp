//
// Created by Tamar M on 2019-09-25.
//

#include <iostream>
#include "Cards.h"

using namespace std;

int main() {

    // init deck
    Deck deck = Deck();

    // generate the cards
    deck.generateDeck();
    cout << "***********************************" << endl;
    cout << "** DECK AFTER INITIAL GENERATION **" << endl;
    cout << "***********************************" << endl;
    deck.printDeck();

    // shuffle the deck
    deck.shuffle();
    cout << "************************" << endl;
    cout << "** DECK AFTER SHUFFLE **" << endl;
    cout << "************************" << endl;
    deck.printDeck();

    // draw initial hand
    Hand hand = Hand(&deck);

    // perform exchanges
    int index = 0;
    while(index > -1) {
        hand.printHand();
        cout << "Enter the index of a card or a negative number to exit: ";
        cin >> index;
        Card *card = hand.exchange(index, 14);
        cout << "Exchanged for the following card: " << endl;
        card->printCard();
    }

    return 0;
}