//
// Created by MJ on 2019-11-22.
//

#include <iostream>
#include "../Cards.h"

using namespace std;

class GameCard {
protected:
    Card* card;
public:
    GameCard() = default;

    virtual ~GameCard() {
        delete card;
    }

    virtual void printCard() = 0;
};

class RubyCard : public GameCard {
public:
    RubyCard(Action action) {
        this->card = new Card(Good(Good::GoodType::GOOD_RUBY, 1), action);
    }

    void printCard() {
        cout << "This is a Ruby Card!" << endl;
        this->card->printCard();
    }
};

class WoodCard : public GameCard {
public:
    WoodCard(Action action) {
        this->card = new Card(Good(Good::GoodType::GOOD_WOOD, 1), action);
    }

    void printCard() {
        cout << "This is a Wood Card!" << endl;
        this->card->printCard();

    }
};

class CarrotCard : public GameCard {
public:
    CarrotCard(Action action) {
        this->card = new Card(Good(Good::GoodType::GOOD_CARROT, 1), action);

    }

    void printCard() {
        cout << "This is a Carrot Card!" << endl;
        this->card->printCard();

    }
};

class AnvilCard : public GameCard {
public:
    AnvilCard(Action action) {
        this->card = new Card(Good(Good::GoodType::GOOD_ANVIL, 1), action);

    }

    void printCard() {
        cout << "This is an Anvil Card!" << endl;
        this->card->printCard();
    }
};

class OreCard : public GameCard {
public:
    OreCard(Action action) {
        this->card = new Card(Good(Good::GoodType::GOOD_ORE, 1), action);

    }

    void printCard() {
        cout << "This is an Ore Card!" << endl;
        this->card->printCard();
    }
};

class WildCard : public GameCard {
public:
    WildCard(Action action) {
        this->card = new Card(Good(Good::GoodType::GOOD_WILD, 1), action);

    }

    void printCard() {
        cout << "This is a Wild Card!" << endl;
        this->card->printCard();
    }
};

