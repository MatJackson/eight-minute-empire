//
// Created by Tamar M on 2019-11-09.
//

#ifndef EIGHT_MINUTE_EMPIRE_PLAYERSTRATEGIES_H
#define EIGHT_MINUTE_EMPIRE_PLAYERSTRATEGIES_H

#include "../Cards/Cards.h"

class PlayerStrategy {
public:
    virtual int pickCard(Hand* hand) = 0;
};


class HumanStrategy : public PlayerStrategy {
public:
    int pickCard(Hand* hand);
};

class GreedyComputerStrategy : public PlayerStrategy {
    // greedy computer player that focuses on building cities or destroying opponents
public:
    int pickCard(Hand* hand);
};

class ModerateComputerStrategy : public PlayerStrategy {
    //a moderate computer player that control a region in which it just needs to occupy it with more armies than the opponents
public:
    int pickCard(Hand* hand);
};


#endif //EIGHT_MINUTE_EMPIRE_PLAYERSTRATEGIES_H
