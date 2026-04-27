#pragma once
#include <QObject>

enum class ButtonStatus {
    ACTIVE,
    INACTIVE
};

class BaseButton : public QObject {
    Q_OBJECT
protected:
    ButtonStatus status_;

public:
    explicit BaseButton(QObject* parent = nullptr);
    ~BaseButton() override = default;
};
