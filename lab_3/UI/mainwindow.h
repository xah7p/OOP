#pragma once

#include "EntityId.h"

#include <QMainWindow>

class QComboBox;
class QLineEdit;
class QListWidget;
class QPushButton;
class QTableWidget;
class QTabWidget;
class Plane;

class MainWindow: public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    void onLoadModelBtnClicked();
    void onShiftBtnClicked();
    void onScaleBtnClicked();
    void onRotateBtnClicked();
    void addCameraBtnClicked();
    void onUndoBtnClicked();
    void onSetActiveBtnClicked();
    void onComposeBtnClicked();
    void contextMenuRequested(const QPoint &pos);
    void deleteObjectRequested();
    void setActiveCamRequested();
    void composeRequested();

private:
    void createUi();
    void createScene();
    QLineEdit *makeEdit(QWidget *parent, const QString &placeholder) const;
    void insertRow(EntityId id, const QString &name, const QString &type);
    std::vector<int> selectedRows() const;
    void logOperation(const QString &text);

    Plane *planeWidget = nullptr;
    QTabWidget *tabWidget = nullptr;
    QComboBox *modelReprList = nullptr;
    QComboBox *cameraTypeList = nullptr;
    QPushButton *loadModelBtn = nullptr;
    QPushButton *createCameraBtn = nullptr;
    QLineEdit *dxOffsetInput = nullptr;
    QLineEdit *dyOffsetInput = nullptr;
    QLineEdit *dzOffsetInput = nullptr;
    QLineEdit *kScale = nullptr;
    QLineEdit *angleXRotate = nullptr;
    QLineEdit *angleYRotate = nullptr;
    QLineEdit *angleZRotate = nullptr;
    QPushButton *applyShiftBtn = nullptr;
    QPushButton *applyScaleBtn = nullptr;
    QPushButton *applyRotateBtn = nullptr;
    QPushButton *undoBtn = nullptr;
    QPushButton *setActiveBtn = nullptr;
    QPushButton *composeBtn = nullptr;
    QTableWidget *tableWidget = nullptr;
    QListWidget *operationsList = nullptr;

    EntityId objects = 0;
    EntityId activeCamId = 0;
};
