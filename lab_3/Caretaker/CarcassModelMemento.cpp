#include "CarcassModelMemento.h"

#include "CarcassModelEntity.h"
#include "CarcassModelStructure.h"

CarcassModelMemento::CarcassModelMemento(const CarcassModelEntity& value):
    entity(nullptr)
{
    auto cloned = value.clone();
    if (cloned)
        set(std::unique_ptr<BaseEntity>(cloned.get()));
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
