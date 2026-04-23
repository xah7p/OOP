#pragma once

#include "BaseVisitor.h"
#include "TransformData.h"

class TransformVisitor: public BaseVisitor {
public:
    TransformVisitor() = delete;
    TransformVisitor(std::shared_ptr<TransformData> action);
    TransformVisitor(const TransformVisitor& other) = default;
    TransformVisitor(TransformVisitor&& other) = default;

    TransformVisitor& operator=(const TransformVisitor& other) = default;
    TransformVisitor& operator=(TransformVisitor&& other) = default;

    virtual ~TransformVisitor() = 0;

    virtual void visit(std::shared_ptr<CarcassModelStructure>) override;
    virtual void visit(std::shared_ptr<CameraEntityStructure>) override;
protected:
    std::shared_ptr<TransformData> action;
};