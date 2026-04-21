#include "QtDrawFactory.h"

#include "QtPainter.h"

QtDrawFactory::QtDrawFactory(std::shared_ptr<QGraphicsScene> scene):
    scene(std::move(scene))
{ }

std::shared_ptr<BasePainter> QtDrawFactory::createPainter()
{
    return std::make_shared<QtPainter>(scene);
}
