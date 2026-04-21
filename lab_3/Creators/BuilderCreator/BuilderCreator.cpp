#include "BuilderCreator.h"

#include "CarcassModelBuilder.h"
#include "DefaultCameraBuilder.h"
#include "ListCarcassModelStructure.h"
#include "MatrixCarcassModelStructure.h"

std::shared_ptr<BaseBuilder> ListCarcassModelBuilderCreator::create(const std::shared_ptr<BaseReader>& reader) const
{
    auto modelReader = std::dynamic_pointer_cast<CarcassModelReader>(reader);
    if (!modelReader)
        return nullptr;
    return std::make_shared<CarcassModelBuilder>(modelReader, std::make_shared<ListCarcassModelStructure>());
}

std::shared_ptr<BaseBuilder> MatrixCarcassModelBuilderCreator::create(const std::shared_ptr<BaseReader>& reader) const
{
    auto modelReader = std::dynamic_pointer_cast<CarcassModelReader>(reader);
    if (!modelReader)
        return nullptr;
    return std::make_shared<CarcassModelBuilder>(modelReader, std::make_shared<MatrixCarcassModelStructure>());
}

std::shared_ptr<BaseBuilder> DefaultCameraBuilderCreator::create(const std::shared_ptr<BaseReader>& reader) const
{
    auto cameraReader = std::dynamic_pointer_cast<DefaultCameraReader>(reader);
    if (!cameraReader)
        return nullptr;
    return std::make_shared<DefaultCameraBuilder>(cameraReader);
}
