#pragma once 

#include "BaseCameraCommand.h"
#include "CameraManager.h"
#include "EntityId.h"

class CameraAddCommand: public BaseCameraCommand {
private:
    using ManagerMethod = void (CameraManager::*)(const EntityId&);

    EntityId cameraId;
    ManagerMethod method;
    std::shared_ptr<CameraManager> manager;
public:
    CameraAddCommand(const EntityId& id);
    virtual ~CameraAddCommand() override = default;

    void execute() override;
};
