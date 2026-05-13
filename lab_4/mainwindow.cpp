#include "mainwindow.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "Defines.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(this)
    , currentFloorValue(nullptr) {
    ui->setupUi(this);
    generateUi();
    QObject::connect(this, &MainWindow::requestFloorSignal, &controller, &Controller::newTargetSlot);
    QObject::connect(&controller, &Controller::toMoveCabinSignal, this, [this](int floor, Direction) {
        updateFloorIndicator(floor);
        if (callButtons.contains(floor))
            callButtons[floor]->deactivateSignal();
        if (cabinButtons.contains(floor))
            cabinButtons[floor]->deactivateSignal();
    });
    QObject::connect(&controller, &Controller::reachedTargetSignal, this, [this](int floor) {
        updateFloorIndicator(floor);
        if (callButtons.contains(floor))
            callButtons[floor]->deactivateSignal();
        if (cabinButtons.contains(floor))
            cabinButtons[floor]->deactivateSignal();
    });
    updateFloorIndicator(START_FLOOR);
}

void MainWindow::generateUi() {
    setWindowTitle("Система управления лифтом");
    setStyleSheet("background-color: #f0f0f0; font-family: Arial, sans-serif;");

    auto rootLayout = new QHBoxLayout(ui->centralwidget);
    rootLayout->setContentsMargins(20, 20, 20, 20);
    rootLayout->setSpacing(24);

    auto callColumn = new QVBoxLayout();
    auto callTitle = new QLabel("Этажи");
    callTitle->setAlignment(Qt::AlignCenter);
    callTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #202020;");
    callColumn->addWidget(callTitle);

    for (int floor = FLOOR_COUNT; floor >= 1; --floor) {
        auto row = new QHBoxLayout();

        auto floorLabel = new QLabel(QString::number(floor));
        floorLabel->setAlignment(Qt::AlignCenter);
        floorLabel->setFixedSize(40, 36);
        floorLabel->setStyleSheet(
            "background-color: #e6e6e6; color: #101010; border: 1px solid #909090; "
            "border-radius: 8px; font-weight: bold; font-size: 14px;");

        auto callButton = new Button("●", floor, this);
        callButton->setFixedSize(44, 36);
        callButtons.insert(floor, callButton);
        setCallButtonActive(floor, false);
        QObject::connect(callButton, &Button::activatedSignal, this, [this](int requestedFloor) {
            setCallButtonActive(requestedFloor, true);
            emit requestFloorSignal(requestedFloor);
        });
        QObject::connect(callButton, &Button::deactivatedSignal, this, [this](int requestedFloor) {
            setCallButtonActive(requestedFloor, false);
        });

        row->addWidget(floorLabel);
        row->addWidget(callButton);
        callColumn->addLayout(row);
    }

    auto cabinColumn = new QVBoxLayout();
    auto cabinTitle = new QLabel("Кабина");
    cabinTitle->setAlignment(Qt::AlignCenter);
    cabinTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #202020;");
    cabinColumn->addWidget(cabinTitle);

    for (int floor = FLOOR_COUNT; floor >= 1; --floor) {
        auto cabinButton = new Button(QString::number(floor), floor, this);
        cabinButton->setFixedSize(70, 36);
        cabinButtons.insert(floor, cabinButton);
        setCabinButtonActive(floor, false);
        QObject::connect(cabinButton, &Button::activatedSignal, this, [this](int requestedFloor) {
            setCabinButtonActive(requestedFloor, true);
            emit requestFloorSignal(requestedFloor);
        });
        QObject::connect(cabinButton, &Button::deactivatedSignal, this, [this](int requestedFloor) {
            setCabinButtonActive(requestedFloor, false);
        });
        cabinColumn->addWidget(cabinButton, 0, Qt::AlignCenter);
    }

    auto indicatorColumn = new QVBoxLayout();
    auto indicatorTitle = new QLabel("Индикатор");
    indicatorTitle->setAlignment(Qt::AlignCenter);
    indicatorTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #202020;");
    indicatorColumn->addWidget(indicatorTitle);

    auto currentFloorLabel = new QLabel("Текущий этаж");
    currentFloorLabel->setAlignment(Qt::AlignCenter);
    currentFloorLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #202020;");
    indicatorColumn->addWidget(currentFloorLabel);

    currentFloorValue = new QLabel(QString::number(START_FLOOR));
    currentFloorValue->setAlignment(Qt::AlignCenter);
    currentFloorValue->setFixedSize(120, 120);
    currentFloorValue->setStyleSheet(
        "background-color: #a5d6a7; color: #0b2e13; border: 3px solid #2e7d32; border-radius: 18px;"
        "font-size: 52px; font-weight: bold;");
    indicatorColumn->addWidget(currentFloorValue, 0, Qt::AlignCenter);

    auto separator = new QFrame();
    separator->setFrameShape(QFrame::VLine);
    separator->setStyleSheet("color: #b0b0b0;");

    rootLayout->addLayout(callColumn, 1);
    rootLayout->addWidget(separator);
    rootLayout->addLayout(cabinColumn, 1);
    rootLayout->addLayout(indicatorColumn, 1);
}

void MainWindow::setCallButtonActive(int floor, bool isActive) {
    if (!callButtons.contains(floor))
        return;
    if (isActive) {
        callButtons[floor]->setStyleSheet(
            "QPushButton { background-color: #404040; color: white; border: 2px solid #202020; border-radius: 8px; }");
    } else {
        callButtons[floor]->setStyleSheet(
            "QPushButton { background-color: #d0d0d0; color: #101010; border: 2px solid #808080; border-radius: 8px; }"
            "QPushButton:hover { background-color: #b0b0b0; }");
    }
}

void MainWindow::setCabinButtonActive(int floor, bool isActive) {
    if (!cabinButtons.contains(floor))
        return;

    if (isActive)
        cabinButtons[floor]->activateSignal();
    else
        cabinButtons[floor]->deactivateSignal();

    int currentFloor = START_FLOOR;
    if (currentFloorValue)
        currentFloor = currentFloorValue->text().toInt();
    refreshCabinButtonStyle(floor, currentFloor);
}

void MainWindow::refreshCabinButtonStyle(int floor, int currentFloor) {
    if (!cabinButtons.contains(floor))
        return;

    const bool isActive = cabinButtons[floor]->isActive();
    const bool isCurrentFloor = (floor == currentFloor);

    if (isCurrentFloor && isActive) {
        cabinButtons[floor]->setStyleSheet(
            "QPushButton { background-color: #2e7d32; color: white; border: 3px solid #1b5e20; border-radius: 8px; font-weight: bold; }"
            "QPushButton:hover { background-color: #388e3c; }");
    } else if (isCurrentFloor) {
        cabinButtons[floor]->setStyleSheet(
            "QPushButton { background-color: #a5d6a7; color: #0b2e13; border: 3px solid #2e7d32; border-radius: 8px; font-weight: bold; }"
            "QPushButton:hover { background-color: #81c784; }");
    } else if (isActive) {
        cabinButtons[floor]->setStyleSheet(
            "QPushButton { background-color: #404040; color: white; border: 2px solid #202020; border-radius: 8px; font-weight: bold; }");
    } else {
        cabinButtons[floor]->setStyleSheet(
            "QPushButton { background-color: #e0e0e0; color: #101010; border: 2px solid #808080; border-radius: 8px; font-weight: bold; }"
            "QPushButton:hover { background-color: #c0c0c0; }");
    }
}

void MainWindow::updateFloorIndicator(int floor) {
    if (currentFloorValue)
        currentFloorValue->setText(QString::number(floor));

    for (int cabinFloor = 1; cabinFloor <= FLOOR_COUNT; ++cabinFloor)
        refreshCabinButtonStyle(cabinFloor, floor);
}

MainWindow::~MainWindow() {
    delete ui;
}
