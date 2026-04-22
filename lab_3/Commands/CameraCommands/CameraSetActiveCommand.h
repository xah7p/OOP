#pragma once 

#include "BaseCameraCommand.h"
#include "CameraManager.h"
#include "EntityId.h"

class CameraSetActiveCommand: public BaseCameraCommand {
private:
    using ManagerMethod = void (CameraManager::*)(const EntityId&);

    EntityId cameraId;
    ManagerMethod method;
    std::shared_ptr<CameraManager> manager;
public:
    CameraSetActiveCommand(const EntityId& id);
    virtual ~CameraSetActiveCommand() override = default;

    void execute() override;
};
