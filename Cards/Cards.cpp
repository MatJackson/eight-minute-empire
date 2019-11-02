//
// Created by Tamar M on 2019-09-25.
//

#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>
#include "Cards.h"

Action::Action(Action::ActionType type, int count): type(type), count(count) {
}

const char * const Action::actions[] = {
        "Add army",
        "Move over land",
        "Move over land and water",
        "build city",
        "destroy army"
};

string Action::getName() {
    return actions[type];
}

Good::Good(Good::GoodType type, int count): type(type), count(count) {
}

const char * const Good::goods[] = {
        "Ruby",
        "Wood",
        "Carrot",
        "Anvil",
        "Ore",
        "Wild"
};

string Good::getName() {
    return goods[type];
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

string Card::getCombinationType() {
    switch (combinationType) {
        case 0: return "SINGLE";
        case 1: return "OR";
        case 2: return "AND";
    }
}

void Card::printCard() {
    cout << "\tGood: " << good.getName() << " (" << good.count << ")" << endl;
    cout << "\tAction: " << actions[0].getName() << " (" << actions[0].count << ")" << endl;
    if (actions.size() == 2) {
        combinationType == 1 ? cout << "\tOR" << endl : cout << "\tAND" << endl;
        cout << "\tAction: " << actions[1].getName() << " (" << actions[1].count << ")" << endl;
    }
}

Deck::Deck() {
    topCard = &cards[0];
}

Hand::Hand(Deck *deck): deck(deck) {
    for (int i = 0; i < 6; i++) {
        cards[i] = deck->draw();
    }
}

void Deck::shuffle() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

Card* Deck::draw() {
    Card *card = topCard;
    topCard++;
    return card;
}

void Deck::printDeck() {
    for (int i = 0; i < 42; i++) {
        cout << "Card " << i+1 << endl;
        cards[i].printCard();
        cout << endl;
    }
}

int Hand::cardCost(int cardIndex) {
    switch (cardIndex) {
        case 0: return 0;
        case 1:
        case 2: return 1;
        case 3:
        case 4: return 2;
        case 5: return 3;
        default: return 100; // ensures player can't afford card if index is out of bounds
    }
}

void Hand::shiftCards(int index) {
    for (int i = index; i < 5; i++) {
        cards[i] = cards[i+1];
    }
}

Card* Hand::exchange(int cardIndex, int *coins) {
    // check if player can afford exchange
    if (cardCost(cardIndex) > *coins) {
        return nullptr;
    }

    // pay the piper
    *coins = *coins - cardCost(cardIndex);

    // save reference to card
    Card *card = (cards[cardIndex]);

    // shift cards to new positions
    shiftCards(cardIndex);

    // draw new card
    cards[5] = deck->draw();

    return card;
}

void Hand::printHand() {
    for (int i = 0; i < 187; i++) {
        cout << "*";
    }
    printf("\n|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|\n",
           cards[0]->good.getName().c_str(), cards[0]->good.count,
           cards[1]->good.getName().c_str(), cards[1]->good.count,
           cards[2]->good.getName().c_str(), cards[2]->good.count,
           cards[3]->good.getName().c_str(), cards[3]->good.count,
           cards[4]->good.getName().c_str(), cards[4]->good.count,
           cards[5]->good.getName().c_str(), cards[5]->good.count
    );

    printf("|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|\n",
           cards[0]->actions[0].getName().c_str(), cards[0]->actions[0].count,
           cards[1]->actions[0].getName().c_str(), cards[1]->actions[0].count,
           cards[2]->actions[0].getName().c_str(), cards[2]->actions[0].count,
           cards[3]->actions[0].getName().c_str(), cards[3]->actions[0].count,
           cards[4]->actions[0].getName().c_str(), cards[4]->actions[0].count,
           cards[5]->actions[0].getName().c_str(), cards[5]->actions[0].count
    );

    printf("|%-30s|%-30s|%-30s|%-30s|%-30s|%-30s|\n",
           cards[0]->combinationType == 0 ? "" : cards[0]->getCombinationType().c_str(),
           cards[1]->combinationType == 0 ? "" : cards[1]->getCombinationType().c_str(),
           cards[2]->combinationType == 0 ? "" : cards[2]->getCombinationType().c_str(),
           cards[3]->combinationType == 0 ? "" : cards[3]->getCombinationType().c_str(),
           cards[4]->combinationType == 0 ? "" : cards[4]->getCombinationType().c_str(),
           cards[5]->combinationType == 0 ? "" : cards[5]->getCombinationType().c_str()
    );

    printf("|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|%-27s(%-1d)|\n",
           cards[0]->combinationType == 0 ? "" : cards[0]->actions[1].getName().c_str(),
           cards[0]->combinationType == 0 ? 0 : cards[0]->actions[1].count,
           cards[1]->combinationType == 0 ? "" : cards[1]->actions[1].getName().c_str(),
           cards[1]->combinationType == 0 ? 0 : cards[1]->actions[1].count,
           cards[2]->combinationType == 0 ? "" : cards[2]->actions[1].getName().c_str(),
           cards[2]->combinationType == 0 ? 0 : cards[2]->actions[1].count,
           cards[3]->combinationType == 0 ? "" : cards[3]->actions[1].getName().c_str(),
           cards[3]->combinationType == 0 ? 0 : cards[3]->actions[1].count,
           cards[4]->combinationType == 0 ? "" : cards[4]->actions[1].getName().c_str(),
           cards[4]->combinationType == 0 ? 0 : cards[4]->actions[1].count,
           cards[5]->combinationType == 0 ? "" : cards[5]->actions[1].getName().c_str(),
           cards[5]->combinationType == 0 ? 0 : cards[5]->actions[1].count
    );

    printf("|%-30s|%-30s|%-30s|%-30s|%-30s|%-30s|\n",
            "Cost: 0", "Cost: 1", "Cost: 1", "Cost: 2", "Cost: 2", "Cost: 3"
    );

    for (int i = 0; i < 187; i++) {
        cout << "*";
    }
    cout << endl;

}

void Deck::generateDeck() {

    // Wood (8 Cards)
    cards[0] = Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    cards[1] = Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[2] = Card( // 5 player card
            Good(Good::GoodType::GOOD_WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 6)
    );

    cards[3] = Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_DESTROY_ARMY, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[4] = Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 2),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    cards[5] = Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 4)
    );

    cards[6] = Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[7] = Card(
            Good(Good::GoodType::GOOD_WOOD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    // Carrot (10 Cards)
    cards[8] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[9] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Card::CombinationType::AND,
            Action(Action::ACTION_DESTROY_ARMY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 1)
    );

    cards[10] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[11] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[12] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 5)
    );

    cards[13] = Card(
            Good(Good::GoodType::GOOD_CARROT, 2),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[14] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[15] = Card( // 5 player card
            Good(Good::GoodType::GOOD_CARROT, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 4),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[16] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[17] = Card(
            Good(Good::GoodType::GOOD_CARROT, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    // ANVIL (9 Cards)
    cards[18] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[19] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 3),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[20] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 5)
    );

    cards[21] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[22] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[23] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[24] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Action(Action::ActionType::ACTION_BUILD_CITY, 1)
    );

    cards[25] = Card( // 5 player card
            Good(Good::GoodType::GOOD_ANVIL, 2),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 4)
    );

    cards[26] = Card(
            Good(Good::GoodType::GOOD_ANVIL, 1),
            Card::CombinationType::OR,
            Action(Action::ACTION_ADD_ARMY, 3),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 3)
    );

    // ORE (7 Cards)
    cards[27] = Card(
            Good(Good::GoodType::GOOD_ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[28] = Card(
            Good(Good::GoodType::GOOD_ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[29] = Card( // 5 player card
            Good(Good::GoodType::GOOD_ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 2)
    );

    cards[30] = Card(
            Good(Good::GoodType::GOOD_ORE, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND_OR_WATER, 3)
    );

    cards[31] = Card(
            Good(Good::GoodType::GOOD_ORE, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[32] = Card(
            Good(Good::GoodType::GOOD_ORE, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 3)
    );

    cards[33] = Card(
            Good(Good::GoodType::GOOD_ORE, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    // RUBY (5 Cards)
    cards[34] = Card(
            Good(Good::GoodType::GOOD_RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    cards[35] = Card(
            Good(Good::GoodType::GOOD_RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    cards[36] = Card(
            Good(Good::GoodType::GOOD_RUBY, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[37] = Card(
            Good(Good::GoodType::GOOD_RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 1)
    );

    cards[38] = Card( // 5 player card
            Good(Good::GoodType::GOOD_RUBY, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

    // WILD (3 Cards)
    cards[39] = Card(
            Good(Good::GoodType::GOOD_WILD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[40] = Card(
            Good(Good::GoodType::GOOD_WILD, 1),
            Action(Action::ActionType::ACTION_MOVE_OVER_LAND, 2)
    );

    cards[41] = Card(
            Good(Good::GoodType::GOOD_WILD, 1),
            Action(Action::ActionType::ACTION_ADD_ARMY, 2)
    );

}


