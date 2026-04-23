#pragma once

#include "InvisibleEntity.h"
#include "CameraEntityStructure.h"

class BaseCameraEntity : public InvisibleEntity {
public:
    virtual ~BaseCameraEntity() override = default;
};
