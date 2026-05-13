#include "BaseButton.h"

BaseButton::BaseButton(QObject* parent)
    : QObject(parent)
    , status_(ButtonStatus::INACTIVE) {}
