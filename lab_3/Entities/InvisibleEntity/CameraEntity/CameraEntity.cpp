#include "CameraEntity.h"
#include "DefaultCameraEntityStructure.h"

namespace
{
std::shared_ptr<CameraEntityStructure> cloneStructure(const std::shared_ptr<CameraEntityStructure>& source)
{
    if (!source)
        return nullptr;

    if (auto camera = std::dynamic_pointer_cast<DefaultCameraEntityStructure>(source))
        return std::make_shared<DefaultCameraEntityStructure>(*camera);

    return nullptr;
}
}  

CameraEntity::CameraEntity(std::shared_ptr<CameraEntityStructure> structure):
    structure(std::move(structure))
{ }

CameraEntity::CameraEntity(const CameraEntity& other) = default;
CameraEntity::CameraEntity(CameraEntity&& other) = default;
CameraEntity& CameraEntity::operator=(const CameraEntity& other) = default;
CameraEntity& CameraEntity::operator=(CameraEntity&& other) = default;

void CameraEntity::accept(std::shared_ptr<BaseVisitor> visitor)
{
    if (structure)
        visitor->visit(structure);
}

std::shared_ptr<CameraEntityStructure> CameraEntity::getStructure() const noexcept
{
    return structure;
}

std::unique_ptr<Memento> CameraEntity::createMemento() const
{
    auto memento = std::make_unique<Memento>();
    auto clonedStructure = cloneStructure(structure);
    if (clonedStructure)
        memento->set(std::make_unique<CameraEntity>(clonedStructure));
    return memento;
}

void CameraEntity::restoreMemento(std::unique_ptr<Memento> memento)
{
    if (!memento)
        return;
    auto entity = memento->get();
    auto restored = dynamic_cast<CameraEntity*>(entity.release());
    if (!restored)
        return;
    structure = cloneStructure(restored->structure);
    delete restored;
}
