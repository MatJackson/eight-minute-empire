//
// Created by MJ on 2019-11-22.
//

#include <iostream>
#include "CardsFactory.h"

using namespace std;

int main() {

    // Create a Ruby Card
    GameCard* rubyCard = CardsFactory::create("ruby", Action(Action::ActionType::ACTION_ADD_ARMY, 3));
    rubyCard->printCard();
    cout << endl;

    // Create a Wood Card
    GameCard* woodCard = CardsFactory::create("wood", Action(Action::ActionType::ACTION_ADD_ARMY, 3));
    woodCard->printCard();
    cout << endl;

    // Create a Carrot Card
    GameCard* carrotCard = CardsFactory::create("carrot", Action(Action::ActionType::ACTION_ADD_ARMY, 3));
    carrotCard->printCard();
    cout << endl;

    // Create an Anvil Card
    GameCard* anvilCard = CardsFactory::create("anvil", Action(Action::ActionType::ACTION_ADD_ARMY, 3));
    anvilCard->printCard();
    cout << endl;

    // create an Ore Card
    GameCard* oreCard = CardsFactory::create("ore", Action(Action::ActionType::ACTION_ADD_ARMY, 3));
    oreCard->printCard();
    cout << endl;

    // create a Wild Card
    GameCard* wildCard = CardsFactory::create("wild", Action(Action::ActionType::ACTION_ADD_ARMY, 3));
    wildCard->printCard();
    cout << endl;

    delete rubyCard;
    delete woodCard;
    delete carrotCard;
    delete anvilCard;
    delete oreCard;
    delete wildCard;

    cout << "enter any input to exit";
    cin.get();
    return 0;
}

