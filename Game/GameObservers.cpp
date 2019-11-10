//
// Created by Tamar M on 2019-11-10.
//

#include "GameObservers.h"

Observer::Observer(){
};

Subject::Subject(){
    observers = new list<Observer*>;
}

void Subject::Attach(Observer* o) {
    observers->push_back(o);
};

void Subject::Detach(Observer* o) {
    observers->remove(o);
};

void Subject::Notify() {
    list<Observer *>::iterator i;
    for (i = observers->begin(); i != observers->end(); ++i)
        (*i)->Update();
};