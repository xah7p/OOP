#pragma once

#include <cstddef>
#include <QGraphicsScene>
#include "Vertex.h"
#include "BasePainter.h"

class QtPainter: public BasePainter {
private:
    std::shared_ptr<QGraphicsScene> graphicsScene;

public:
    QtPainter() = delete;
    QtPainter(std::shared_ptr<QGraphicsScene> scene);

    virtual ~QtPainter() override = default;

    virtual void drawLine(const Vertex &vertex1, const Vertex &vertex2) override;
    virtual void clear() override;

    virtual void setWidht(size_t width) const noexcept override;
    virtual void setHeight(size_t height) const noexcept override;

    virtual size_t getWidht() const noexcept override;
    virtual size_t getHeight() const noexcept override;
};