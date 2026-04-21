#pragma once

#include "BaseCameraBuilder.h"
#include "CameraEntity.h"
#include "DefaultCameraEntityStructure.h"
#include "Quaternion.h"
#include "Vertex.h"

#include <memory>

class DefaultCameraBuilder: public BaseCameraBuilder {
private:
    Vertex viewpoint;
    Quaternion quaternion;
    double fovY;
    double nearZ;
    double farZ;
protected:
    std::shared_ptr<BaseEntity> createEntity() override;
public:
    DefaultCameraBuilder() = delete;
    explicit DefaultCameraBuilder(std::shared_ptr<DefaultCameraReader> reader);

    ~DefaultCameraBuilder() override = default;

    bool buildViewpoint() override;
    bool buildQuaternion() override;
    bool buildProjection() override;
};
