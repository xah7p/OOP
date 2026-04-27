#pragma once

#include <QObject>
#include "../Controller/Controller.h"

class Elevator : public QObject {
    Q_OBJECT
private:
    Controller controller_;

public:
    explicit Elevator(QObject *parent = nullptr);
    ~Elevator() = default;
};
