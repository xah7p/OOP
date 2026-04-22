#pragma once

#include "BaseVisitor.h"
#include "Memento.h"
#include "Vertex.h"

#include <initializer_list>
#include <memory>
#include <map>
#include <cstddef>
#include <optional>

class BaseEntity;

using BaseEntityPtr = std::shared_ptr<BaseEntity>;
using BaseEntityMap = std::map<size_t, BaseEntityPtr>;

class BaseEntity {
public:
    using value_type = BaseEntityPtr;
    using size_type = size_t;
    using iterator = BaseEntityMap::iterator;
    using const_iterator = BaseEntityMap::const_iterator;

    virtual ~BaseEntity() = default;
    
    virtual bool isVisible() const noexcept { return true; }
    virtual bool isComposite() const noexcept { return false; }

    virtual bool add(std::initializer_list<BaseEntityPtr> li) { return false; }
    virtual bool remove(const iterator& it) noexcept { return false; }

    virtual iterator begin() const { return iterator(); }
    virtual iterator end() const { return iterator(); }
    virtual const_iterator cbegin() const { return const_iterator(); }
    virtual const_iterator cend() const { return const_iterator(); }
    virtual std::optional<Vertex> getCenter() const { return std::nullopt; }

    virtual void accept(std::shared_ptr<BaseVisitor>) = 0;
    virtual std::shared_ptr<BaseEntity> clone() const = 0;

    virtual std::unique_ptr<Memento> createMemento() const = 0;
    virtual void restoreMemento(std::unique_ptr<Memento>) = 0;
};
