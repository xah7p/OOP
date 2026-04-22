#include "CameraEntity.h"
#include "MementoCreator.h"

CameraEntity::CameraEntity(std::shared_ptr<CameraEntityStructure> structure):
    structure(std::move(structure))
{ }

CameraEntity::CameraEntity(const CameraEntity& other) = default;
CameraEntity::CameraEntity(CameraEntity&& other) = default;
CameraEntity& CameraEntity::operator=(const CameraEntity& other) = default;
CameraEntity& CameraEntity::operator=(CameraEntity&& other) = default;

void CameraEntity::accept(std::shared_ptr<BaseVisitor> visitor)
{
    if (structure)
        visitor->visit(structure);
}

std::shared_ptr<CameraEntityStructure> CameraEntity::accept() const
{
    return structure;
}

std::optional<Vertex> CameraEntity::getCenter() const
{
    return structure ? std::optional<Vertex>(structure->getViewpoint()) : std::nullopt;
}

std::shared_ptr<BaseEntity> CameraEntity::clone() const
{
    if (!structure)
        return std::make_shared<CameraEntity>(nullptr);
    return std::make_shared<CameraEntity>(structure->clone());
}

void CameraEntity::assignStateFrom(const BaseEntity& other)
{
    *this = static_cast<const CameraEntity&>(other);
}

std::unique_ptr<BaseMemento> CameraEntity::createMemento() const
{
    if (!structure)
        return nullptr;
    return MementoCreator::create<CameraMemento>(*this);
}

void CameraEntity::restoreMemento(std::unique_ptr<BaseMemento> memento)
{
    if (!memento)
        return;

    auto restoredEntity = memento->get();
    if (!restoredEntity)
        return;
    assignStateFrom(*restoredEntity);
}
