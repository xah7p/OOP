#pragma once

#include <QObject>
#include "../Defines.h"
#include "../Doors/Doors.h"

enum class CabinStatus {
    REACHED,
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
    void cabinOpenDoorsSignal();
    void cabinUnlockedSignal();

public slots:
    void cabinMoveSlot(int floor, Direction direction);
    void cabinReachedSlot();
    void cabinLockSlot();
    void cabinUnlockSlot();
};
