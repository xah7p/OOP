#include "CarcassModelEntity.h"

CarcassModelEntity::CarcassModelEntity(std::shared_ptr<CarcassModelStructure> structure):
    structure(std::move(structure))
{ }

CarcassModelEntity::CarcassModelEntity(const CarcassModelEntity& other) = default;
CarcassModelEntity::CarcassModelEntity(CarcassModelEntity&& other) = default;
CarcassModelEntity& CarcassModelEntity::operator=(const CarcassModelEntity& other) = default;
CarcassModelEntity& CarcassModelEntity::operator=(CarcassModelEntity&& other) = default;

void CarcassModelEntity::accept(std::shared_ptr<BaseVisitor> visitor)
{
    if (structure)
        visitor->visit(structure);
}

std::shared_ptr<CarcassModelStructure> CarcassModelEntity::accept() const
{
    return structure;
}

std::optional<Vertex> CarcassModelEntity::getCenter() const
{
    return structure ? std::optional<Vertex>(structure->getCenter()) : std::nullopt;
}

std::shared_ptr<BaseEntity> CarcassModelEntity::clone() const
{
    if (!structure)
        return std::make_shared<CarcassModelEntity>(nullptr);
    return std::make_shared<CarcassModelEntity>(structure->clone());
}

std::unique_ptr<Memento> CarcassModelEntity::createMemento() const
{
    auto memento = std::make_unique<Memento>();
    if (structure)
        memento->set(std::make_unique<CarcassModelEntity>(structure->clone()));
    return memento;
}

void CarcassModelEntity::restoreMemento(std::unique_ptr<Memento> memento)
{
    if (!memento)
        return;
    auto entity = memento->get();
    auto restored = dynamic_cast<CarcassModelEntity*>(entity.release());
    if (!restored)
        return;
    structure = restored->structure ? restored->structure->clone() : nullptr;
    delete restored;
}
