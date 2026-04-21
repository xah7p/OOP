#include "Composite.h"
#include "CarcassModelEntity.h"
#include "CameraEntity.h"
#include "ListCarcassModelStructure.h"
#include "MatrixCarcassModelStructure.h"
#include "DefaultCameraEntityStructure.h"

#include <cstdarg>

namespace
{
std::shared_ptr<BaseEntity> cloneEntity(const std::shared_ptr<BaseEntity>& source)
{
    if (!source)
        return nullptr;

    if (auto model = std::dynamic_pointer_cast<CarcassModelEntity>(source))
    {
        auto structure = model->getStructure();
        if (auto list = std::dynamic_pointer_cast<ListCarcassModelStructure>(structure))
            return std::make_shared<CarcassModelEntity>(std::make_shared<ListCarcassModelStructure>(*list));
        if (auto matrix = std::dynamic_pointer_cast<MatrixCarcassModelStructure>(structure))
            return std::make_shared<CarcassModelEntity>(std::make_shared<MatrixCarcassModelStructure>(*matrix));
        return nullptr;
    }

    if (auto camera = std::dynamic_pointer_cast<CameraEntity>(source))
    {
        auto structure = camera->getStructure();
        if (auto def = std::dynamic_pointer_cast<DefaultCameraEntityStructure>(structure))
            return std::make_shared<CameraEntity>(std::make_shared<DefaultCameraEntityStructure>(*def));
        return nullptr;
    }

    if (auto composite = std::dynamic_pointer_cast<Composite>(source))
    {
        auto out = std::make_shared<Composite>();
        for (auto it = composite->cbegin(); it != composite->cend(); ++it)
        {
            auto child = cloneEntity(it->second);
            if (child)
                out->add({child});
        }
        return out;
    }

    return nullptr;
}
}  

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
        auto cloned = cloneEntity(item.second);
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
            auto cloned = cloneEntity(item.second);
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

std::unique_ptr<Memento> Composite::createMemento() const
{
    auto memento = std::make_unique<Memento>();
    auto cloned = std::make_unique<Composite>(*this);
    memento->set(std::move(cloned));
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
