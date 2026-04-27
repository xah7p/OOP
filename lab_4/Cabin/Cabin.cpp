#include "Cabin.h"

Cabin::Cabin(QObject* parent)
    : QObject(parent)
    , status_(CabinStatus::UNLOCKED)
    , lastMoveFromFloor_(START_FLOOR)
    , lastMoveDirection_(Direction::UP) {
    moveTimer_.setSingleShot(true);
    QObject::connect(&moveTimer_, &QTimer::timeout, this, &Cabin::onMoveTimeoutSlot);
    QObject::connect(this, &Cabin::cabinOpenDoorsSignal, &doors_, &Doors::startOpeningSlot);
    QObject::connect(&doors_, &Doors::doorIsClosedSignal, this, &Cabin::cabinUnlockSlot);
}

void Cabin::onMoveTimeoutSlot() {
    emit movementTickSignal(lastMoveFromFloor_, lastMoveDirection_);
}

void Cabin::cabinMoveSlot(int floor, Direction direction) {
    if (status_ == CabinStatus::LOCKED)
        return;
    status_ = CabinStatus::MOVING;
    lastMoveFromFloor_ = floor;
    lastMoveDirection_ = direction;

    qInfo(TEXT_BLUE "Лифт едет c этажа №%d на этаж №%d." TEXT_DEFAULT, floor, floor + direction);
    moveTimer_.start(MOVE_TIME);
}

void Cabin::cabinStopSlot(int floor) {
    if (status_ == CabinStatus::MOVING) {
        status_ = CabinStatus::STOPPED;
        qInfo(TEXT_BLUE "Лифт остановился на этаже №%d" TEXT_DEFAULT, floor);
    }

    emit cabinStoppedSignal();
}

void Cabin::cabinLockSlot() {
    if (status_ == CabinStatus::MOVING)
        return;
    auto previousStatus = status_;
    status_ = CabinStatus::LOCKED;

    if (previousStatus != CabinStatus::LOCKED)
        qInfo(TEXT_BLUE "Кабина заблокирована" TEXT_DEFAULT);
    emit cabinOpenDoorsSignal();
}

void Cabin::cabinUnlockSlot() {
    if (status_ != CabinStatus::LOCKED)
        return;
    status_ = CabinStatus::UNLOCKED;

    qInfo(TEXT_BLUE "Кабина разблокирована" TEXT_DEFAULT);
    emit cabinUnlockedSignal();
}
