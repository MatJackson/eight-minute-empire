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