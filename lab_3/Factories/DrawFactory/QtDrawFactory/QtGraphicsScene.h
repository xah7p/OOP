#pragma once

#include <cstddef>
#include <memory>
#include <QGraphicsScene>

#include "BaseGraphicsScene.h"

class QtGraphicsScene: public BaseGraphicsScene
{
public:
    QtGraphicsScene(size_t width, size_t height);
    ~QtGraphicsScene() override = default;

    void addLine(double x1, double y1, double x2, double y2) override;
    void clear() override;

    void setSceneRect(double x, double y, double width, double height) override;
    double width() const noexcept override;
    double height() const noexcept override;

    void setBackgroundColor(int r, int g, int b) override;

    QGraphicsScene *getRawScene() const noexcept;

private:
    std::shared_ptr<QGraphicsScene> scene;
};
