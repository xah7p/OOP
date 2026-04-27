#include "Doors.h"

Doors::Doors(QObject* parent)
    : QObject(parent)
    , status_(DoorsStatus::CLOSED) {
    openingTimer_.setSingleShot(true);
    closingTimer_.setSingleShot(true);
    stayingOpenTimer_.setSingleShot(true);

    QObject::connect(&openingTimer_, &QTimer::timeout, this, &Doors::openedSlot);
    QObject::connect(&closingTimer_, &QTimer::timeout, this, &Doors::closedSlot);
    QObject::connect(&stayingOpenTimer_, &QTimer::timeout, this, &Doors::startClosingSlot);
}

void Doors::startOpeningSlot() {
    if (status_ != DoorsStatus::CLOSED && status_ != DoorsStatus::CLOSING)
        return;
    auto previousStatus = status_;
    status_ = DoorsStatus::OPENING;

    if (previousStatus == DoorsStatus::CLOSED) {
        qInfo(TEXT_GREEN "Двери лифта начали открываться..." TEXT_DEFAULT);
        openingTimer_.start(DOORS_MOVING_TIME);
    } else {
        int remainingTime = closingTimer_.remainingTime();
        closingTimer_.stop();
        qInfo(TEXT_GREEN "Закрытие дверей прервано" TEXT_DEFAULT);
        qInfo(TEXT_GREEN "Двери лифта начали открываться..." TEXT_DEFAULT);

        int openingTime = DOORS_MOVING_TIME;
        if (remainingTime > 0) {
            openingTime = DOORS_MOVING_TIME - remainingTime;
            if (openingTime < 1)
                openingTime = 1;
            if (openingTime > DOORS_MOVING_TIME)
                openingTime = DOORS_MOVING_TIME;
        }
        openingTimer_.start(openingTime);
    }
}

void Doors::startClosingSlot() {
    if (status_ != DoorsStatus::OPENED)
        return;
    status_ = DoorsStatus::CLOSING;

    qInfo(TEXT_GREEN "Двери лифта начали закрываться..." TEXT_DEFAULT);
    closingTimer_.start(DOORS_MOVING_TIME);
}

void Doors::openedSlot() {
    if (status_ != DoorsStatus::OPENING)
        return;
    status_ = DoorsStatus::OPENED;

    qInfo(TEXT_GREEN "Двери лифта открылись" TEXT_DEFAULT);
    stayingOpenTimer_.start(DOORS_STAYING_OPEN_TIME);
}

void Doors::closedSlot() {
    if (status_ != DoorsStatus::CLOSING)
        return;
    status_ = DoorsStatus::CLOSED;

    qInfo(TEXT_GREEN "Двери лифта закрылись" TEXT_DEFAULT);
    emit doorIsClosedSignal();
}
