//
// Created by Tamar M on 2019-11-10.
//

#ifndef EIGHT_MINUTE_EMPIRE_GAMEOBSERVERS_H
#define EIGHT_MINUTE_EMPIRE_GAMEOBSERVERS_H

#include <list>

using namespace std;

class Observer {
public:
    Observer();
    virtual void Update() = 0;
};

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    list<Observer*> *observers;
};

#endif //EIGHT_MINUTE_EMPIRE_GAMEOBSERVERS_H
