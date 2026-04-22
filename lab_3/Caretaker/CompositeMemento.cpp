#include "CompositeMemento.h"

#include "Composite.h"

CompositeMemento::CompositeMemento(const Composite& value):
    entity(nullptr)
{
    set(std::make_unique<Composite>(value));
}

CompositeMemento::~CompositeMemento() = default;

std::unique_ptr<BaseEntity> CompositeMemento::get()
{
    return std::move(entity);
}

void CompositeMemento::set(std::unique_ptr<BaseEntity> value)
{
    entity = std::move(value);
}
