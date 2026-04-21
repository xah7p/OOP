#pragma once

#include "TransformVisitor.h"

class MoveVisitor: public TransformVisitor {
public:
    MoveVisitor() = delete;
    // MoveVisitor(const MoveArgs &args);
    virtual ~MoveVisitor() = 0;
};