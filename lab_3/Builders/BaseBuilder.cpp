#include "BaseBuilder.h"

std::shared_ptr<BaseEntity> BaseBuilder::getEntity()
{
    if (!entity)
        entity = createEntity();
    return entity;
}
