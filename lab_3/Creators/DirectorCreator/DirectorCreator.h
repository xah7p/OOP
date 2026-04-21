#pragma once

#include <memory>

#include "BaseDirector.h"
#include "BaseBuilder.h"

class BaseDirectorCreator {
public:
    virtual ~BaseDirectorCreator() = default;
    virtual std::unique_ptr<BaseDirector> create(std::shared_ptr<BaseBuilder> builder) const = 0;
};

class CarcassDirectorCreator: public BaseDirectorCreator {
public:
    std::unique_ptr<BaseDirector> create(std::shared_ptr<BaseBuilder> builder) const override;
};

class CameraDirectorCreator: public BaseDirectorCreator {
public:
    std::unique_ptr<BaseDirector> create(std::shared_ptr<BaseBuilder> builder) const override;
};
