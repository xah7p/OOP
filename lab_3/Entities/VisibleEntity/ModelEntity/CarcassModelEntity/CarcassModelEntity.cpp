#include "CarcassModelEntity.h"
#include "ListCarcassModelStructure.h"
#include "MatrixCarcassModelStructure.h"

namespace
{
std::shared_ptr<CarcassModelStructure> cloneStructure(const std::shared_ptr<CarcassModelStructure>& source)
{
    if (!source)
        return nullptr;

    if (auto list = std::dynamic_pointer_cast<ListCarcassModelStructure>(source))
        return std::make_shared<ListCarcassModelStructure>(*list);
    if (auto matrix = std::dynamic_pointer_cast<MatrixCarcassModelStructure>(source))
        return std::make_shared<MatrixCarcassModelStructure>(*matrix);

    return nullptr;
}
}  

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

std::shared_ptr<CarcassModelStructure> CarcassModelEntity::getStructure() const noexcept
{
    return structure;
}

std::unique_ptr<Memento> CarcassModelEntity::createMemento() const
{
    auto memento = std::make_unique<Memento>();
    auto clonedStructure = cloneStructure(structure);
    if (clonedStructure)
        memento->set(std::make_unique<CarcassModelEntity>(clonedStructure));
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
    structure = cloneStructure(restored->structure);
    delete restored;
}
