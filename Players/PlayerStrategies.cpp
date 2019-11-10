//
// Created by Tamar M on 2019-11-09.
//

#include "PlayerStrategies.h"
#include <iostream>

int HumanStrategy::pickCard(Hand *hand) {
    int indexOfCardToExchange;
    while (true) {
        cout << "Please select the index [0-5] of the card you wish to exchange:";
        cin >> indexOfCardToExchange;

        if (cin.fail() || indexOfCardToExchange < 0 || indexOfCardToExchange > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return indexOfCardToExchange;
        }
    }
}

int GreedyComputerStrategy::pickCard(Hand *hand) {
    for(int c = 0; c < 6; c++) {
        vector<Action>::iterator a;
        for (a = (hand->cards[c]->actions).begin(); a !=(hand->cards[c]->actions).end(); ++a) {
            if (a->type == 3 || a->type == 4) {
                return c;
            }
        }
    }

    return 0;
}

int ModerateComputerStrategy::pickCard(Hand *hand) {
    for(int c = 0; c < 6; c++) {
        vector<Action>::iterator a;
        for (a = (hand->cards[c]->actions).begin(); a !=(hand->cards[c]->actions).end(); ++a) {
            if (a->type == 0 || a->type == 1 || a->type == 2) {
                return c;
            }
        }
    }

    return 0;
}

bool PlayerStrategy::interaction() {
    return true;
}

bool HumanStrategy::interaction() {
    return true;
}

bool GreedyComputerStrategy::interaction() {
    return false;
}

bool ModerateComputerStrategy::interaction() {
    return false;
}
