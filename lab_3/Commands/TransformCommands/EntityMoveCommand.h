#pragma once 

#include <memory>
#include "BaseTransformCommand.h"
#include "TransformManager.h"
#include "EntityId.h"
#include "TransformArgs.h"

class EntityMoveCommand: public BaseTransformCommand {
private:
    using ManagerMethod = void (TransformManager::*)(EntityId, const MoveArgs&);

    ManagerMethod method;
    std::shared_ptr<TransformManager> manager;
public:
    EntityMoveCommand();
    virtual ~EntityMoveCommand() override = default;

    void execute() override;
};
