//
// Created by Tamar M on 2019-09-25.
//

#include "Cards.h"

Action::Action(Action::ActionType type, int count): type(type), count(count) {
}

Good::Good(Good::GoodType type, int count): type(type), count(count) {
}

Card::Card(Good good, Action action): good(good), combinationType(CombinationType::SINGLE) {
    actions.insert(actions.begin(), action);
}

Card::Card(Good good, CombinationType combinationType, Action primaryAction, Action secondaryAction):
        good(good),
        combinationType(combinationType) {
    actions.insert(actions.begin(), primaryAction);
    actions.insert(actions.begin(), secondaryAction);
}

void Deck::generateDeck(bool greaterThanFive) {
    // Wood Cards (7)
    cards[0] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    cards[1] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[2] = Card(
            Good(Good::GoodType::WOOD, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_DESTROY_ARMY, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[3] = Card(
            Good(Good::GoodType::WOOD, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 2),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    cards[4] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 4)
    );

    cards[5] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[6] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );
}


