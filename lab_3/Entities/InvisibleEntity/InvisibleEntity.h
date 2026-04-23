#pragma once

#include "BaseEntity.h"

class InvisibleEntity : public BaseEntity {
public: 
    virtual ~InvisibleEntity() override = default;
    virtual bool isVisible() const noexcept override { return false; }
};
