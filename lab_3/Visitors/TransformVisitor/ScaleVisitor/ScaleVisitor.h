#pragma once

#include "TransformVisitor.h"
#include "TransformArgs.h"

class ScaleVisitor: public TransformVisitor {
public:
    ScaleVisitor() = delete;
    ScaleVisitor(const ScaleArgs &args);
    virtual ~ScaleVisitor() override = default;
};