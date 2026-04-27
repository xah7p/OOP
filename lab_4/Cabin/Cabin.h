#pragma once

#include <QObject>
#include "../Defines.h"
#include "../Doors/Doors.h"

class Controller;

enum class CabinStatus {
    STOPPED,
    MOVING,
    LOCKED,
    UNLOCKED
};

class Cabin : public QObject {
    Q_OBJECT
private:
    CabinStatus status_;
    Doors doors_;
    QTimer moveTimer_;
    int lastMoveFromFloor_;
    Direction lastMoveDirection_;

public:
    Cabin(QObject* parent = nullptr);
    ~Cabin() = default;

signals:
    void movementTickSignal(int fromFloor, Direction direction);
    void cabinStoppedSignal();
    void cabinOpenDoorsSignal();
    void cabinUnlockedSignal();

private slots:
    void onMoveTimeoutSlot();

public slots:
    void cabinMoveSlot(int floor, Direction direction);
    void cabinStopSlot(int floor);
    void cabinLockSlot();
    void cabinUnlockSlot();
};
