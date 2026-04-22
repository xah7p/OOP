#include "CameraEntity.h"

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

std::unique_ptr<Memento> CameraEntity::createMemento() const
{
    auto memento = std::make_unique<Memento>();
    if (structure)
        memento->set(std::make_unique<CameraEntity>(structure->clone()));
    return memento;
}

void CameraEntity::restoreMemento(std::unique_ptr<Memento> memento)
{
    if (!memento)
        return;
    auto entity = memento->get();
    auto restored = dynamic_cast<CameraEntity*>(entity.release());
    if (!restored)
        return;
    structure = restored->structure ? restored->structure->clone() : nullptr;
    delete restored;
}
