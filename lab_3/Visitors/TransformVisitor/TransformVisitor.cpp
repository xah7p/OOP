#include "TransformVisitor.h"

TransformVisitor::TransformVisitor(std::shared_ptr<TransformData> action):
    action(std::move(action))
{ }

TransformVisitor::~TransformVisitor() = default;

void TransformVisitor::visit(std::shared_ptr<CarcassModelStructure> structure) const
{
    if (structure)
        structure->transform(action);
}

void TransformVisitor::visit(std::shared_ptr<CameraEntityStructure> structure) const
{
    if (structure)
        structure->transform(action);
}
