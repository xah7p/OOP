#pragma once

#include "TransformVisitor.h"

class ScaleVisitor: public TransformVisitor {
public:
    ScaleVisitor() = delete;
    // ScaleVisitor(const ScaleArgs &args);
    virtual ~ScaleVisitor() = 0;
};