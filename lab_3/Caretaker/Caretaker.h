#pragma once

#include "Memento.h"
#include "EntityId.h"
#include <list>
#include <memory>

using namespace std;

class Caretaker {
private:
    list<pair<EntityId, unique_ptr<BaseMemento>>> mementos;
public:
    Caretaker() = default;
    ~Caretaker() = default;

    void set(EntityId, unique_ptr<BaseMemento>);
    unique_ptr<BaseMemento> get(EntityId id);
};