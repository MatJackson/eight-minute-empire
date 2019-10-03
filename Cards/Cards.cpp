//
// Created by Tamar M on 2019-09-25.
//

#include <algorithm>
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

Deck::Deck() {
    topCard = &cards[0];
}

void Deck::generateDeck() {
    // Wood (8 Cards)
    cards[0] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    cards[1] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[2] = Card( // 5 player card
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 6)
    );

    cards[3] = Card(
            Good(Good::GoodType::WOOD, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_DESTROY_ARMY, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[4] = Card(
            Good(Good::GoodType::WOOD, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 2),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    cards[5] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 4)
    );

    cards[6] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[7] = Card(
            Good(Good::GoodType::WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    // Carrot (10 Cards)

    cards[8] = Card(
            Good(Good::GoodType::CARROT, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[9] = Card(
            Good(Good::GoodType::CARROT, 1),
            Card::CombinationType::AND,
            Action(Action::ACTION_DESTROY_ARMY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 1)
    );

    cards[10] = Card(
            Good(Good::GoodType::CARROT, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[11] = Card(
            Good(Good::GoodType::CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[12] = Card(
            Good(Good::GoodType::CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 5)
    );

    cards[13] = Card(
            Good(Good::GoodType::CARROT, 2),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[14] = Card(
            Good(Good::GoodType::CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[15] = Card( // 5 player card
            Good(Good::GoodType::CARROT, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 4),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[16] = Card(
            Good(Good::GoodType::CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[17] = Card(
            Good(Good::GoodType::CARROT, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    // ANVIL (9 Cards)

    cards[18] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[19] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 3),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[20] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 5)
    );

    cards[21] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[22] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[23] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[24] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[25] = Card( // 5 player card
            Good(Good::GoodType::ANVIL, 2),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[26] = Card(
            Good(Good::GoodType::ANVIL, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 3),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    // ORE (7 Cards)
    cards[27] = Card(
            Good(Good::GoodType::ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[28] = Card(
            Good(Good::GoodType::ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[29] = Card( // 5 player card
            Good(Good::GoodType::ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 2)
    );

    cards[30] = Card(
            Good(Good::GoodType::ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[31] = Card(
            Good(Good::GoodType::ORE, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[32] = Card(
            Good(Good::GoodType::ORE, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[33] = Card(
            Good(Good::GoodType::ORE, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    // RUBY (5 Cards)

    cards[34] = Card(
            Good(Good::GoodType::RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    cards[35] = Card(
            Good(Good::GoodType::RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    cards[36] = Card(
            Good(Good::GoodType::RUBY, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[37] = Card(
            Good(Good::GoodType::RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 1)
    );

    cards[38] = Card( // 5 player card
            Good(Good::GoodType::RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    // WILD (3 Cards)

    cards[39] = Card(
            Good(Good::GoodType::WILD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[40] = Card(
            Good(Good::GoodType::WILD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[41] = Card(
            Good(Good::GoodType::WILD, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

}

void Deck::shuffle() {
    random_shuffle(begin(cards), end(cards));
}


