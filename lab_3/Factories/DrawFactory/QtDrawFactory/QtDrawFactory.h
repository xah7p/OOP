#pragma once

#include <memory>
#include <QGraphicsScene>
#include "BasePainter.h"
#include "BaseDrawFactory.h"

class QtDrawFactory: public BaseDrawFactory {
private:
    std::shared_ptr<QGraphicsScene> scene;
public: 
    QtDrawFactory() = delete;
    QtDrawFactory(std::shared_ptr<QGraphicsScene> scene);
    virtual ~QtDrawFactory() override = default;

    virtual std::shared_ptr<BasePainter> createPainter() override;
};