#include "CarcassDirector.h"

#include "BaseModelBuilder.h"

CarcassDirector::CarcassDirector(std::shared_ptr<BaseBuilder> builder)
{
    this->builder = std::move(builder);
}

std::shared_ptr<BaseEntity> CarcassDirector::create() const
{
    auto modelBuilder = std::dynamic_pointer_cast<BaseModelBuilder>(builder);
    if (!modelBuilder)
        return nullptr;

    modelBuilder->buildVertixes();
    modelBuilder->buildEdges();
    modelBuilder->buildCenter();
    return modelBuilder->getEntity();
}
