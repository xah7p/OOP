#pragma once

#include "BaseCameraEntity.h"
#include "CameraEntityStructure.h"

class CameraEntity: public BaseCameraEntity {
private:
    std::shared_ptr<CameraEntityStructure> structure;
public:
    CameraEntity() = default;
    CameraEntity(std::shared_ptr<CameraEntityStructure>);

    explicit CameraEntity(const CameraEntity& other);
    CameraEntity(CameraEntity&& other);  
    
    CameraEntity& operator=(const CameraEntity& other);
    CameraEntity& operator=(CameraEntity&& other);   

    virtual ~CameraEntity() override = default;

    virtual void accept(std::shared_ptr<BaseVisitor>) override;
    virtual std::shared_ptr<CameraEntityStructure> accept() const override;
    virtual std::optional<Vertex> getCenter() const override;
    virtual std::shared_ptr<BaseEntity> clone() const override;

    virtual std::unique_ptr<Memento> createMemento() const override;
    virtual void restoreMemento(std::unique_ptr<Memento>) override;
};
