#include "Composite.h"
#include "MementoCreator.h"

#include <cstdarg>

Composite::Composite(BaseEntityPtr first, ...)
{
    if (!first)
        return;

    entities[size++] = std::move(first);

    va_list args;
    va_start(args, first);
    while (auto* raw = va_arg(args, BaseEntity*))
    {
        entities[size++] = BaseEntityPtr(raw);
    }
    va_end(args);
}

Composite::Composite(const Composite& other):
    entities(), size(0)
{
    for (const auto& item : other.entities)
    {
        auto cloned = item.second ? item.second->clone() : nullptr;
        if (cloned)
            entities[size++] = cloned;
    }
}

Composite::Composite(Composite&& other):
    entities(std::move(other.entities)), size(other.size)
{
    other.size = 0;
}

Composite& Composite::operator=(const Composite& other)
{
    if (this != &other)
    {
        entities.clear();
        size = 0;
        for (const auto& item : other.entities)
        {
            auto cloned = item.second ? item.second->clone() : nullptr;
            if (cloned)
                entities[size++] = cloned;
        }
    }
    return *this;
}

Composite& Composite::operator=(Composite&& other)
{
    if (this != &other)
    {
        entities = std::move(other.entities);
        size = other.size;
        other.size = 0;
    }
    return *this;
}

bool Composite::add(std::initializer_list<BaseEntityPtr> li)
{
    for (auto&& entity : li)
    {
        if (!entity)
            continue;
        entities[size++] = entity;
    }
    return true;
}

bool Composite::remove(const iterator& it) noexcept
{
    if (it == entities.end())
        return false;
    entities.erase(it);
    return true;
}

Composite::iterator Composite::begin() const
{
    return const_cast<Composite*>(this)->entities.begin();
}

Composite::iterator Composite::end() const
{
    return const_cast<Composite*>(this)->entities.end();
}

Composite::const_iterator Composite::cbegin() const
{
    return entities.cbegin();
}

Composite::const_iterator Composite::cend() const
{
    return entities.cend();
}

void Composite::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto& item : entities)
        item.second->accept(visitor);
}

std::optional<Vertex> Composite::getCenter() const
{
    Vertex sum(0.0, 0.0, 0.0);
    size_t count = 0;
    for (auto it = entities.cbegin(); it != entities.cend(); ++it)
    {
        auto center = it->second ? it->second->getCenter() : std::nullopt;
        if (!center)
            continue;
        sum += *center;
        ++count;
    }
    if (count == 0)
        return std::nullopt;
    sum.setX(sum.getX() / static_cast<double>(count));
    sum.setY(sum.getY() / static_cast<double>(count));
    sum.setZ(sum.getZ() / static_cast<double>(count));
    return sum;
}

std::shared_ptr<BaseEntity> Composite::clone() const
{
    return std::make_shared<Composite>(*this);
}

std::unique_ptr<BaseMemento> Composite::createMemento() const
{
    return MementoCreator::create<CompositeMemento>(*this);
}

void Composite::assignStateFrom(const BaseEntity& other)
{
    const Composite& snapshot = static_cast<const Composite&>(other);
    if (size != snapshot.size)
    {
        *this = snapshot;
        return;
    }
    for (size_t i = 0; i < size; ++i)
    {
        if (!entities.contains(i) || !snapshot.entities.contains(i))
        {
            *this = snapshot;
            return;
        }
        BaseEntityPtr live = entities[i];
        BaseEntityPtr snap = snapshot.entities.at(i);
        if (!live || !snap)
            continue;
        live->assignStateFrom(*snap);
    }
}

void Composite::restoreMemento(std::unique_ptr<BaseMemento> memento)
{
    if (!memento)
        return;

    auto restoredEntity = memento->get();
    if (!restoredEntity)
        return;
    assignStateFrom(*restoredEntity);
}

