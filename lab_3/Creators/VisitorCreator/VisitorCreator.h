#pragma once

#include "Concepts.h"
#include "TransformArgs.h"

#include "RotateVisitor.h"
#include "BaseVisitor.h"
#include "MoveVisitor.h"
#include "RotateVisitor.h"
#include "ScaleVisitor.h"

#include "DrawVisitor.h"
#include "BasePainter.h"
#include "BaseCameraEntity.h"

#include <memory>

template <typename AbstractVisitor, typename DerivedVisitor, typename... Args>
requires Derivative<DerivedVisitor, AbstractVisitor> && Constructible<DerivedVisitor, Args...>
class VisitorCreator
{
public:
    VisitorCreator() = default;
    ~VisitorCreator() = default;

    template <typename... CallArgs>
    static std::shared_ptr<BaseVisitor> create(CallArgs &&...args);
};

using RotateVisitorCreator = VisitorCreator<BaseVisitor, RotateVisitor, RotateArgs>;

using MoveVisitorCreator = VisitorCreator<BaseVisitor, MoveVisitor, MoveArgs>;

using ScaleVisitorCreator = VisitorCreator<BaseVisitor, ScaleVisitor, ScaleArgs>;

using DrawVisitorCreator = VisitorCreator<BaseVisitor, DrawVisitor, 
    std::shared_ptr<BaseCameraEntity>, 
    std::shared_ptr<BasePainter>,
    std::shared_ptr<BaseCenterStrategy>,
    std::shared_ptr<BaseProjectionStrategy>,
    std::shared_ptr<BaseRemovingInvisibleLinesStrategy>>;