#include "Button.h"
#include <QDebug>
#include "../Defines.h"

Button::Button(const QString& text, int floor, QWidget* parent)
    : QPushButton(text, parent)
    , floor_(floor)
    , status_(ButtonStatus::INACTIVE) {
    QObject::connect(this, &QPushButton::clicked, this, &Button::activateSlot);
    QObject::connect(this, &Button::activateSignal, this, &Button::activateSlot);
    QObject::connect(this, &Button::deactivateSignal, this, &Button::deactivateSlot);
}

void Button::setFloor(int floor) {
    floor_ = floor;
}

bool Button::isActive() const noexcept {
    return status_ == ButtonStatus::ACTIVE;
}

void Button::activateSlot() {
    if (status_ == ButtonStatus::ACTIVE)
        return;
    status_ = ButtonStatus::ACTIVE;

    qInfo(TEXT_GREEN "На этаже №%d была активирована кнопка" TEXT_DEFAULT, floor_);
    emit activatedSignal(floor_);
}

void Button::deactivateSlot() {
    if (status_ == ButtonStatus::INACTIVE)
        return;
    status_ = ButtonStatus::INACTIVE;

    qInfo(TEXT_GREEN "На этаже №%d была деактивирована кнопка" TEXT_DEFAULT, floor_);
    emit deactivatedSignal(floor_);
}
