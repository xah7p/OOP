#include "QtDrawFactory.h"

#include "QtGraphicsScene.h"
#include "QtPainter.h"

std::shared_ptr<BaseGraphicsScene> QtDrawFactory::createGraphicsScene(size_t width, size_t height)
{
    return std::make_shared<QtGraphicsScene>(width, height);
}

std::shared_ptr<BasePainter> QtDrawFactory::createPainter(std::shared_ptr<BaseGraphicsScene> scene)
{
    return std::make_shared<QtPainter>(std::move(scene));
}
