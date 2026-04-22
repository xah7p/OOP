#pragma once

#include "BaseModelEntity.h"
#include "CarcassModelStructure.h"

class CarcassModelEntity: public BaseModelEntity {
private:
    std::shared_ptr<CarcassModelStructure> structure;
public:
    CarcassModelEntity() = default;
    CarcassModelEntity(std::shared_ptr<CarcassModelStructure>);

    explicit CarcassModelEntity(const CarcassModelEntity& other);
    CarcassModelEntity(CarcassModelEntity&& other);  
    
    CarcassModelEntity& operator=(const CarcassModelEntity& other);
    CarcassModelEntity& operator=(CarcassModelEntity&& other);   

    virtual ~CarcassModelEntity() override = default;

    virtual void accept(std::shared_ptr<BaseVisitor>) override;
    virtual std::shared_ptr<CarcassModelStructure> accept() const override;
    virtual void assignStateFrom(const BaseEntity& other) override;
    virtual std::optional<Vertex> getCenter() const override;

    virtual std::shared_ptr<BaseEntity> clone() const override;
    
    virtual std::unique_ptr<BaseMemento> createMemento() const override;
    virtual void restoreMemento(std::unique_ptr<BaseMemento>) override;
};
