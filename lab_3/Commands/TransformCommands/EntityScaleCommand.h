#pragma once 

#include <memory>
#include "BaseTransformCommand.h"
#include "TransformManager.h"
#include "EntityId.h"
#include "TransformArgs.h"

class EntityScaleCommand: public BaseTransformCommand {
private:
    using ManagerMethod = void (TransformManager::*)(EntityId, const ScaleArgs&);

    ManagerMethod method;
    std::shared_ptr<TransformManager> manager;
public:
    EntityScaleCommand();
    virtual ~EntityScaleCommand() override = default;

    void execute() override;
};
