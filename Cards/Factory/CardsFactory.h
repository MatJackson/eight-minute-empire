//
// Created by MJ on 2019-11-22.
//

#ifndef EIGHT_MINUTE_EMPIRE_CARDSFACTORY_H
#define EIGHT_MINUTE_EMPIRE_CARDSFACTORY_H

#endif //EIGHT_MINUTE_EMPIRE_CARDSFACTORY_H

#include <string>
#include "GameCard.cpp"

using namespace std;

class CardsFactory {
private:
    CardsFactory(){};
public:
    static GameCard* create(string goodType, Action action) {
        if (goodType == "ruby")   return new RubyCard(action);
        if (goodType == "wood")   return new WoodCard(action);
        if (goodType == "carrot") return new CarrotCard(action);
        if (goodType == "anvil")  return new AnvilCard(action);
        if (goodType == "ore")    return new OreCard(action);
        if (goodType == "wild")   return new WildCard(action);
        return nullptr;
    }
};
