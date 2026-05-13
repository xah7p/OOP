#pragma once

#include <QPushButton>
#include "BaseButton.h"

class Button : public QPushButton {
    Q_OBJECT
private:
    int floor_;
    ButtonStatus status_;

public:
    Button(const QString& text, int floor, QWidget* parent = nullptr);
    ~Button() override = default;

    void setFloor(int floor);
    [[nodiscard]] bool isActive() const noexcept;

signals:
    void activateSignal();
    void deactivateSignal();

    void activatedSignal(int floor);
    void deactivatedSignal(int floor);

public slots:
    void activateSlot();
    void deactivateSlot();
};
