#pragma once

#include "Facade.h"

#include <QGraphicsView>
#include <QElapsedTimer>
#include <QPoint>

class Plane : public QGraphicsView
{
private:
    QPoint pressStarted;
    bool lookMode = false;
    QElapsedTimer drawTimer;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:
    explicit Plane(QWidget *parent = nullptr);
};
