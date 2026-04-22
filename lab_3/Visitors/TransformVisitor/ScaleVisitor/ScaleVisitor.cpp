#include "ScaleVisitor.h"

ScaleVisitor::ScaleVisitor(const ScaleArgs &args):
    TransformVisitor(std::make_shared<TransformData>(args))
{ }
