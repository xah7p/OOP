#pragma once

#include <QObject>
#include "../Cabin/Cabin.h"
#include "../Defines.h"
#include "../TaskManager/TaskManager.h"

enum class ControllerStatus {
    FREE,
    NEW_TARGET,
    PROCESSING_TARGET,
    REACHED_TARGET
};

class Controller : public QObject {
    Q_OBJECT
private:
    ControllerStatus status_;
    Cabin cabin_;
    int currentFloor_;
    Direction currentDirection_;
    TaskManager taskManager_;

    Direction getDirection(int floor) const;

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller() = default;

signals:
    void toMoveCabinSignal(int floor, Direction direction);
    void toStopCabinSignal(int floor);
    void toLockCabinSignal();

    void reachedTargetSignal(int floor);
    void nextTargetSignal();
    void noTargetsSignal();

public slots:
    void newTargetSlot(int floor);

private slots:
    void handleMovementSlot();
    void targetReachedSlot(int floor);
    void cabinStoppedSlot();
    void freeSlot();
};
