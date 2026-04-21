#include "RotateVisitor.h"

RotateVisitor::RotateVisitor(const RotateArgs &args):
    TransformVisitor(std::make_shared<TransformData>(args))
{ }
