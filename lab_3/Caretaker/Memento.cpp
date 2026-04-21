#include "Memento.h"
#include "BaseEntity.h"

Memento::~Memento() = default;

void Memento::set(std::unique_ptr<BaseEntity> value)
{
    entity = std::move(value);
}

std::unique_ptr<BaseEntity> Memento::get()
{
    return std::move(entity);
}
