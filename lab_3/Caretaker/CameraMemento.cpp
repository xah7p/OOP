#include "CameraMemento.h"

#include "CameraEntity.h"
#include "CameraEntityStructure.h"

CameraMemento::CameraMemento(const CameraEntity& value):
    entity(nullptr)
{
    auto cloned = value.clone();
    if (cloned)
        set(std::unique_ptr<BaseEntity>(cloned.get()));
}

CameraMemento::~CameraMemento() = default;

std::unique_ptr<BaseEntity> CameraMemento::get()
{
    return std::move(entity);
}

void CameraMemento::set(std::unique_ptr<BaseEntity> value)
{
    entity = std::move(value);
}
