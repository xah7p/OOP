#include "DirectorCreator.h"

#include "CarcassDirector.h"
#include "CameraDirector.h"

std::unique_ptr<BaseDirector> CarcassDirectorCreator::create(std::shared_ptr<BaseBuilder> builder) const
{
    return std::make_unique<CarcassDirector>(std::move(builder));
}

std::unique_ptr<BaseDirector> CameraDirectorCreator::create(std::shared_ptr<BaseBuilder> builder) const
{
    return std::make_unique<CameraDirector>(std::move(builder));
}
