#include "BaseModelBuilder.h"

BaseModelBuilder::BaseModelBuilder(std::shared_ptr<CarcassModelReader> reader):
    reader(std::move(reader))
{ }
