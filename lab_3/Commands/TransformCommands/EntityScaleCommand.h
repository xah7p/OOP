#pragma once 

#include <memory>
#include "BaseTransformCommand.h"
#include "TransformManager.h"
#include "EntityId.h"
#include "TransformArgs.h"

class EntityScaleCommand: public BaseTransformCommand {
private:
    using ManagerMethod = void (TransformManager::*)(EntityId, const ScaleArgs&);

    EntityId entityId;
    ScaleArgs args;
    ManagerMethod method;
    std::shared_ptr<TransformManager> manager;
public:
    EntityScaleCommand(EntityId id, const ScaleArgs& args);
    virtual ~EntityScaleCommand() override = default;

    void execute() override;
};
