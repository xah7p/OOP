#pragma once

#include "BaseBuilder.h"
#include "DefaultCameraReader.h"

#include <memory>

enum class CameraBuildPart : size_t {
    Viewpoint = 0,
    Quaternion,
    Projection
};

class BaseCameraBuilder: public BaseBuilder {
protected:
    std::shared_ptr<DefaultCameraReader> reader;
public:
    BaseCameraBuilder() = delete;
    explicit BaseCameraBuilder(std::shared_ptr<DefaultCameraReader> reader);
    ~BaseCameraBuilder() override = default;

    virtual bool buildViewpoint() = 0;
    virtual bool buildQuaternion() = 0;
    virtual bool buildProjection() = 0;
};
