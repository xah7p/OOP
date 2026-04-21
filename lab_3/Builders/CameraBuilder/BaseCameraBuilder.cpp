#include "BaseCameraBuilder.h"

BaseCameraBuilder::BaseCameraBuilder(std::shared_ptr<DefaultCameraReader> reader):
    reader(std::move(reader))
{ }
