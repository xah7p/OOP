#include "CarcassModelEntity.h"
#include "MementoCreator.h"

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

void CarcassModelEntity::assignStateFrom(const BaseEntity& other)
{
    *this = static_cast<const CarcassModelEntity&>(other);
}

std::unique_ptr<BaseMemento> CarcassModelEntity::createMemento() const
{
    if (!structure)
        return nullptr;
    return MementoCreator::create<CarcassModelMemento>(*this);
}

void CarcassModelEntity::restoreMemento(std::unique_ptr<BaseMemento> memento)
{
    if (!memento)
        return;

    auto restoredEntity = memento->get();
    if (!restoredEntity)
        return;
    assignStateFrom(*restoredEntity);
}
