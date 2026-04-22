#pragma once 

#include "BaseCameraCommand.h"
#include "CameraManager.h"
#include "EntityId.h"

class CameraDeleteCommand: public BaseCameraCommand {
private:
    using ManagerMethod = void (CameraManager::*)(const EntityId&);

    EntityId cameraId;
    ManagerMethod method;
    std::shared_ptr<CameraManager> manager;
public:
    CameraDeleteCommand(const EntityId& id);
    virtual ~CameraDeleteCommand() override = default;

    void execute() override;
};
