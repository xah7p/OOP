#pragma once

#include "BaseManager.h"
#include "EntityId.h"
#include "Caretaker.h"
#include <memory>

class HistoryManager : public BaseManager {
private:
    std::shared_ptr<Caretaker> caretaker;
public:
    HistoryManager();
    virtual ~HistoryManager() = default;

    void saveState(EntityId id);
    void restoreState(EntityId id);
};