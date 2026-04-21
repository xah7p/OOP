#pragma once

#include "BaseEntity.h"

#include <initializer_list>
#include <memory>

class Composite : public BaseEntity {
private:
    BaseEntityMap entities;
    size_t size = 0;
public:
    Composite() = default;
    Composite(BaseEntityPtr first, ...);

    explicit Composite(const Composite& other);
    Composite(Composite&& other);  
    
    Composite& operator=(const Composite& other);
    Composite& operator=(Composite&& other); 
    
    virtual ~Composite() = default;
    
    virtual bool isComposite() const noexcept override { return true; }

    virtual bool add(std::initializer_list<BaseEntityPtr> li)  override;
    virtual bool remove(const iterator& it) noexcept override;

    virtual iterator begin() const override;
    virtual iterator end() const override;
    virtual const_iterator cbegin() const override;
    virtual const_iterator cend() const override;

    virtual void accept(std::shared_ptr<BaseVisitor>) override;

    virtual std::unique_ptr<Memento> createMemento() const override;
    virtual void restoreMemento(std::unique_ptr<Memento>) override;
};
