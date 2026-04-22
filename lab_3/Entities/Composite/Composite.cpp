#include "Composite.h"

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

std::unique_ptr<Memento> Composite::createMemento() const
{
    auto memento = std::make_unique<Memento>();
    memento->set(std::make_unique<Composite>(*this));
    return memento;
}

void Composite::restoreMemento(std::unique_ptr<Memento> memento)
{
    if (!memento)
        return;
    auto restored = memento->get();
    auto composite = dynamic_cast<Composite*>(restored.release());
    if (!composite)
        return;
    entities = std::move(composite->entities);
    size = composite->size;
    delete composite;
}
