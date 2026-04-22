#include "MoveVisitor.h"

MoveVisitor::MoveVisitor(const MoveArgs &args):
    TransformVisitor(std::make_shared<TransformData>(args))
{ }
