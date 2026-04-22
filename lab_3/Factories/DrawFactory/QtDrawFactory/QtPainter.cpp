#include "QtPainter.h"

QtPainter::QtPainter(std::shared_ptr<BaseGraphicsScene> scene):
    graphicsScene(std::move(scene))
{ }

void QtPainter::drawLine(const Vertex &vertex1, const Vertex &vertex2)
{
    if (!graphicsScene)
        return;
    graphicsScene->addLine(vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY());
}

void QtPainter::clear()
{
    if (graphicsScene)
        graphicsScene->clear();
}

void QtPainter::setWidht(size_t width) const noexcept
{
    if (graphicsScene)
        graphicsScene->setSceneRect(0.0, 0.0, static_cast<double>(width), graphicsScene->height());
}

void QtPainter::setHeight(size_t height) const noexcept
{
    if (graphicsScene)
        graphicsScene->setSceneRect(0.0, 0.0, graphicsScene->width(), static_cast<double>(height));
}

size_t QtPainter::getWidht() const noexcept
{
    return graphicsScene ? static_cast<size_t>(graphicsScene->width()) : 0U;
}

size_t QtPainter::getHeight() const noexcept
{
    return graphicsScene ? static_cast<size_t>(graphicsScene->height()) : 0U;
}
