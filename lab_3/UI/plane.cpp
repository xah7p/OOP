#include "plane.h"

#include "EntityRotateCommand.h"
#include "CameraGetActiveIdCommand.h"
#include "DrawCommand.h"

#include <QMouseEvent>
#include <algorithm>

Plane::Plane(QWidget *parent):
    QGraphicsView(parent)
{
    setMouseTracking(true);
    drawTimer.start();
}

void Plane::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        lookMode = true;
        pressStarted = event->pos();
        return;
    }
    QGraphicsView::mousePressEvent(event);
    pressStarted = event->pos();
}

void Plane::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        lookMode = false;
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void Plane::mouseMoveEvent(QMouseEvent *event)
{
    if (!lookMode)
    {
        QGraphicsView::mouseMoveEvent(event);
        pressStarted = event->pos();
        return;
    }

    auto offset = event->pos() - pressStarted;
    if (offset.manhattanLength() == 0)
        return;
    if (drawTimer.elapsed() < 16)
    {
        pressStarted = event->pos();
        return;
    }
    const int dx = std::clamp(offset.x(), -25, 25);
    const int dy = std::clamp(offset.y(), -25, 25);
    constexpr double sensitivity = 0.0050;
    RotateArgs args(-static_cast<double>(dy) * sensitivity,
                    -static_cast<double>(dx) * sensitivity,
                    0.0, 0.0, 0.0, 0.0);

    EntityId activeCameraId = 0;
    Facade::instance()->execute(std::make_shared<CameraGetActiveIdCommand>(activeCameraId));
    auto command = std::make_shared<EntityRotateCommand>(activeCameraId, args);
    Facade::instance()->execute(command);
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    drawTimer.restart();

    pressStarted = event->pos();
}
