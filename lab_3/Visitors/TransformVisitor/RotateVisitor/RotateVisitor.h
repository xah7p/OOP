#pragma once

#include "TransformVisitor.h"
#include "TransformArgs.h"

class RotateVisitor: public TransformVisitor {
public:
    RotateVisitor() = delete;
    RotateVisitor(const RotateArgs &args);
    virtual ~RotateVisitor() override = default;
};