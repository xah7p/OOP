#pragma once

class BaseGraphicsScene
{
public:
    BaseGraphicsScene() = default;
    virtual ~BaseGraphicsScene() = default;

    virtual void addLine(double x1, double y1, double x2, double y2) = 0;
    virtual void clear() = 0;

    virtual void setSceneRect(double x, double y, double width, double height) = 0;
    virtual double width() const noexcept = 0;
    virtual double height() const noexcept = 0;

    virtual void setBackgroundColor(int r, int g, int b) = 0;
};
