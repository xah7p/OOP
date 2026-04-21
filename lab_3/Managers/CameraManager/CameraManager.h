#pragma once

#include "BaseCameraEntity.h"
#include "BaseManager.h"
#include <memory>

class CameraManager: public BaseManager {
private:
    std::shared_ptr<BaseCameraEntity> activeCamera;
public:
    CameraManager();
    virtual ~CameraManager() override = default;

    void setActiveCamera(std::shared_ptr<BaseCameraEntity>);
    std::shared_ptr<BaseCameraEntity> getActiveCamera();
};