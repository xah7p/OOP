#pragma once

#include "Concepts.h"
#include <memory>
#include "BaseVisitor.h"
#include "RotateVisitor.h"
#include "MoveVisitor.h"
#include "ScaleVisitor.h"

class BaseVisitor;

class BaseVisitorCreator {
public:
    template<Derivative<BaseVisitor> Visitor, typename... Args>
    requires NotAbstract<Visitor> && Constructible<Visitor, Args...>
    static std::unique_ptr<BaseVisitor> create(Args&& ...args) {
        return std::make_unique<BaseVisitor>(forward<Args>(args)...);
    }
};

// using RotateVisitorCreator = BaseVisitorCreator<BaseVisitor, RotateVisitor, RotationParams>;

// using MoveVisitorCreator = BaseVisitorCreator<BaseVisitor, MoveVisitor, MoveParams>;

// using ScaleVisitorCreator = BaseVisitorCreator<BaseVisitor, ScaleVisitor, ScaleParams>;

// using DrawVisitorCreator = BaseVisitorCreator<BaseVisitor, DrawVisitor, std::shared_ptr<BaseProjectionStrategy>,
//                                           std::shared_ptr<BaseRemovingInvisibleLinesStrategy>,
//                                           std::shared_ptr<BaseCenterStrategy>,
//                                           std::shared_ptr<BasePainter>, std::shared_ptr<BaseCamera>>;