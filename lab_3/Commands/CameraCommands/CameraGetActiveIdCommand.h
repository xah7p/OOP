#pragma once

#include "BaseCameraCommand.h"
#include "CameraManager.h"

class CameraGetActiveIdCommand : public BaseCameraCommand {
private:
    EntityId& outId;
    std::shared_ptr<CameraManager> manager;
public:
    explicit CameraGetActiveIdCommand(EntityId& outId);
    ~CameraGetActiveIdCommand() override = default;

    void execute() override;
};
