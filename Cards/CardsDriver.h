//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_CARDSDRIVER_H
#define EIGHT_MINUTE_EMPIRE_CARDSDRIVER_H

#include "Cards.h"

class CardsDriver {

public:
    Deck *deck;
    CardsDriver(int deckSize);
    vector<Card*> newHand();
};

#endif //EIGHT_MINUTE_EMPIRE_CARDSDRIVER_H
