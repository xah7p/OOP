#pragma once

#include <QObject>
#include "../Defines.h"

enum class DoorsStatus {
    OPENED,
    OPENING,
    CLOSING,
    CLOSED
};

class Doors : public QObject {
    Q_OBJECT
private:
    DoorsStatus status_;
    QTimer openingTimer_;
    QTimer closingTimer_;
    QTimer stayingOpenTimer_;

public:
    Doors(QObject* parent = nullptr);
    ~Doors() = default;

signals:
    void doorIsClosedSignal();

private slots:
    void openedSlot();
    void closedSlot();

public slots:
    void startOpeningSlot();
    void startClosingSlot();
};
