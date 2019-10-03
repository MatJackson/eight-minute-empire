//
// Created by Tamar M on 2019-09-25.
//

#include "Cards.h"

Action::Action(Action::ActionType type, int count):
    type(type),
    count(count)
{}

Good::Good(Good::GoodType type, int count):
    type(type),
    count(count)
{}

Card::Card(Card::CombinationType combinationType, vector<Action> &actions, Good good):
    combinationType(combinationType),
    actions(actions),
    good(good)
{}

void Deck::generateDeck(bool greaterThanFive) {

}


