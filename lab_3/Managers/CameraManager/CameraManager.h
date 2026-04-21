#pragma once

#include "BaseCameraEntity.h"
#include "BaseManager.h"
#include "EntityId.h"
#include <memory>

class CameraManager: public BaseManager {
private:
    std::shared_ptr<BaseCameraEntity> activeCamera;
    EntityId activeCameraId = 0;
public:
    CameraManager();
    virtual ~CameraManager() override = default;

    void addCamera(const EntityId& id);
    void removeCamera(const EntityId& id);
    void setActiveCamera(const EntityId& id);
    std::shared_ptr<BaseCameraEntity> getActiveCamera();
    EntityId getActiveCameraId() const noexcept;
};