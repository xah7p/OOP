#pragma once

#include "BaseDirector.h"

#include <memory>

class CameraDirector: public BaseDirector {
public:
    CameraDirector() = delete;
    explicit CameraDirector(std::shared_ptr<BaseBuilder> builder);

    ~CameraDirector() override = default;

    std::shared_ptr<BaseEntity> create() const override;
};
