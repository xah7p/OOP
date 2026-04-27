#include "Controller.h"

Controller::Controller(QObject *parent)
    : QObject(parent)
    , status_(ControllerStatus::FREE)
    , currentFloor_(START_FLOOR)
    , currentDirection_(Direction::UP) {
    QObject::connect(&cabin_, &Cabin::movementTickSignal, this, &Controller::handleMovementSlot);
    QObject::connect(&cabin_, &Cabin::cabinUnlockedSignal, this, &Controller::handleMovementSlot);
    QObject::connect(&cabin_, &Cabin::cabinStoppedSignal, this, &Controller::cabinStoppedSlot);

    QObject::connect(this, &Controller::toMoveCabinSignal, &cabin_, &Cabin::cabinMoveSlot);
    QObject::connect(this, &Controller::toStopCabinSignal, &cabin_, &Cabin::cabinStopSlot);
    QObject::connect(this, &Controller::toLockCabinSignal, &cabin_, &Cabin::cabinLockSlot);

    QObject::connect(this, &Controller::reachedTargetSignal, this, &Controller::targetReachedSlot);
    QObject::connect(this, &Controller::nextTargetSignal, this, &Controller::handleMovementSlot);
    QObject::connect(this, &Controller::noTargetsSignal, this, &Controller::freeSlot);
}

void Controller::handleMovementSlot() {
    if (status_ == ControllerStatus::FREE)
        return;

    auto previousStatus = status_;
    status_ = ControllerStatus::PROCESSING_TARGET;

    if (taskManager_.isEmpty()) {
        qInfo("Нет целей");
        emit noTargetsSignal();
        return;
    }

    if (previousStatus == ControllerStatus::PROCESSING_TARGET)
        currentFloor_ += currentDirection_;

    int targetFloor = taskManager_.frontFloor();
    if (currentFloor_ == targetFloor)
        emit reachedTargetSignal(currentFloor_);
    else {
        if (previousStatus != ControllerStatus::PROCESSING_TARGET)
            currentDirection_ = getDirection(targetFloor);
        emit toMoveCabinSignal(currentFloor_, currentDirection_);
    }
}

void Controller::newTargetSlot(int floor) {
    qInfo("Вызов лифта на этаж №%d", floor);
    auto previousStatus = status_;
    if (previousStatus != ControllerStatus::PROCESSING_TARGET)
        status_ = ControllerStatus::NEW_TARGET;

    if (previousStatus != ControllerStatus::PROCESSING_TARGET && currentFloor_ == floor) {
        if (taskManager_.hasTaskForFloor(floor))
            return;
        taskManager_.addTask(Task(floor));
        emit nextTargetSignal();
        return;
    }

    if (!taskManager_.hasTaskForFloor(floor))
        taskManager_.insertTaskByDirection(floor, currentFloor_, currentDirection_);

    if (previousStatus == ControllerStatus::FREE)
        emit nextTargetSignal();
}

void Controller::targetReachedSlot(int floor) {
    if (status_ != ControllerStatus::PROCESSING_TARGET && status_ != ControllerStatus::NEW_TARGET)
        return;
    status_ = ControllerStatus::REACHED_TARGET;

    taskManager_.removeTask();
    emit toStopCabinSignal(currentFloor_);
}

void Controller::cabinStoppedSlot() {
    if (status_ != ControllerStatus::REACHED_TARGET)
        return;
    emit toLockCabinSignal();
}

void Controller::freeSlot() {
    if (status_ != ControllerStatus::PROCESSING_TARGET)
        return;
    status_ = ControllerStatus::FREE;
    currentDirection_ = Direction::UP;

    qInfo("Лифт перешёл в режим ожидания");
}

Direction Controller::getDirection(int floor) const {
    return floor > currentFloor_ ? Direction::UP : Direction::DOWN;
}
