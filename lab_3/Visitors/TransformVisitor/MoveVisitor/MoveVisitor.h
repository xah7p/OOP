#pragma once

#include "TransformVisitor.h"
#include "TransformArgs.h"

class MoveVisitor: public TransformVisitor {
public:
    MoveVisitor() = delete;
    MoveVisitor(const MoveArgs &args);
    virtual ~MoveVisitor() override = default;
};