#pragma once 

#include <memory>
#include "BaseTransformCommand.h"
#include "HistoryManager.h"
#include "EntityId.h"

class EntityRestoreStateCommand: public BaseTransformCommand {
private:
    using ManagerMethod = void (HistoryManager::*)(EntityId);

    ManagerMethod method;
    std::shared_ptr<HistoryManager> manager;
public:
    EntityRestoreStateCommand();
    virtual ~EntityRestoreStateCommand() override = default;

    void execute() override;
};
