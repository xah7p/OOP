#pragma once

#include <memory>
#include "CarcassModelStructure.h"
#include "CameraEntityStructure.h"

class BaseVisitor {
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visit(std::shared_ptr<CarcassModelStructure>) const = 0;
    virtual void visit(std::shared_ptr<CameraEntityStructure>) const = 0;
};