#pragma once

#include "TransformVisitor.h"

class RotateVisitor: public TransformVisitor {
public:
    RotateVisitor() = delete;
    // RotateVisitor(const RotateArgs &args);
    virtual ~RotateVisitor() = 0;
};