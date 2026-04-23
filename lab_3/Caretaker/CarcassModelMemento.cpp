#include "CarcassModelMemento.h"

#include "CarcassModelEntity.h"
#include "CarcassModelStructure.h"

CarcassModelMemento::CarcassModelMemento(const CarcassModelEntity& value):
    entity(nullptr)
{
    auto structure = value.accept();
    if (structure)
        set(std::make_unique<CarcassModelEntity>(structure->clone()));
}

CarcassModelMemento::~CarcassModelMemento() = default;

std::unique_ptr<BaseEntity> CarcassModelMemento::get()
{
    return std::move(entity);
}

void CarcassModelMemento::set(std::unique_ptr<BaseEntity> value)
{
    entity = std::move(value);
}
