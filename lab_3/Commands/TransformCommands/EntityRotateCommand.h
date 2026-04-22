#pragma once 

#include <memory>
#include "BaseTransformCommand.h"
#include "TransformManager.h"
#include "EntityId.h"
#include "TransformArgs.h"

class EntityRotateCommand: public BaseTransformCommand {
private:
    using ManagerMethod = void (TransformManager::*)(EntityId, const RotateArgs&);

    EntityId entityId;
    RotateArgs args;
    ManagerMethod method;
    std::shared_ptr<TransformManager> manager;
public:
    EntityRotateCommand(EntityId id, const RotateArgs& args);
    virtual ~EntityRotateCommand() override = default;

    void execute() override;
};
