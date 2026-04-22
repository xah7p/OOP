#include "QtGraphicsScene.h"

#include <QColor>
#include <QPen>

QtGraphicsScene::QtGraphicsScene(size_t width, size_t height):
    scene(std::make_shared<QGraphicsScene>(0.0, 0.0, static_cast<qreal>(width), static_cast<qreal>(height)))
{ }

void QtGraphicsScene::addLine(double x1, double y1, double x2, double y2)
{
    if (!scene)
        return;
    scene->addLine(x1, y1, x2, y2, QPen(QColor::fromRgb(216, 217, 218)));
}

void QtGraphicsScene::clear()
{
    if (scene)
        scene->clear();
}

void QtGraphicsScene::setSceneRect(double x, double y, double width, double height)
{
    if (scene)
        scene->setSceneRect(x, y, width, height);
}

double QtGraphicsScene::width() const noexcept
{
    return scene ? scene->width() : 0.0;
}

double QtGraphicsScene::height() const noexcept
{
    return scene ? scene->height() : 0.0;
}

void QtGraphicsScene::setBackgroundColor(int r, int g, int b)
{
    if (scene)
        scene->setBackgroundBrush(QColor::fromRgb(r, g, b));
}

QGraphicsScene *QtGraphicsScene::getRawScene() const noexcept
{
    return scene.get();
}
