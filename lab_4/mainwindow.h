#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QLabel>
#include "Controller/Controller.h"
#include "Buttons/Button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void requestFloorSignal(int floor);

private:
    void generateUi();
    void refreshCabinButtonStyle(int floor, int currentFloor);
    void setCallButtonActive(int floor, bool isActive);
    void setCabinButtonActive(int floor, bool isActive);
    void updateFloorIndicator(int floor);

    Ui::MainWindow* ui;
    QHash<int, Button*> callButtons;
    QHash<int, Button*> cabinButtons;
    QLabel* currentFloorValue;
    Controller controller;
};
#endif // MAINWINDOW_H
