#include "mainwindow.h"

#include "plane.h"

#include "CameraAddCommand.h"
#include "CameraDeleteCommand.h"
#include "CameraSetActiveCommand.h"
#include "DrawCommand.h"
#include "LoadCommand.h"
#include "EntityMoveCommand.h"
#include "EntityScaleCommand.h"
#include "EntityRotateCommand.h"
#include "EntityRestoreStateCommand.h"
#include "EntityDeleteCommand.h"
#include "EntityComposeCommand.h"
#include "QtGraphicsScene.h"

#include <QComboBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QFrame>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDateTime>
#include <algorithm>
#include <cmath>

QLineEdit *MainWindow::makeEdit(QWidget *parent, const QString &placeholder) const
{
    auto *edit = new QLineEdit(parent);
    edit->setAlignment(Qt::AlignCenter);
    edit->setPlaceholderText(placeholder);
    return edit;
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    Facade::instance();
    createUi();
    createScene();

    connect(applyShiftBtn, &QPushButton::clicked, this, &MainWindow::onShiftBtnClicked);
    connect(applyScaleBtn, &QPushButton::clicked, this, &MainWindow::onScaleBtnClicked);
    connect(applyRotateBtn, &QPushButton::clicked, this, &MainWindow::onRotateBtnClicked);
    connect(loadModelBtn, &QPushButton::clicked, this, &MainWindow::onLoadModelBtnClicked);
    connect(createCameraBtn, &QPushButton::clicked, this, &MainWindow::addCameraBtnClicked);
    connect(undoBtn, &QPushButton::clicked, this, &MainWindow::onUndoBtnClicked);
    connect(setActiveBtn, &QPushButton::clicked, this, &MainWindow::onSetActiveBtnClicked);
    connect(composeBtn, &QPushButton::clicked, this, &MainWindow::onComposeBtnClicked);
    connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::contextMenuRequested);

    Facade::instance()->execute(std::make_shared<CameraAddCommand>(objects));
    Facade::instance()->execute(std::make_shared<CameraSetActiveCommand>(objects));
    activeCamId = objects;
    insertRow(objects++, "Камера 1", "Камера");
    logOperation("Создана камера 1 и установлена активной");
}

void MainWindow::createUi()
{
    setWindowTitle("ЛР3 ООП");
    resize(1300, 850);
    auto *central = new QWidget(this);
    setCentralWidget(central);

    operationsList = new QListWidget(central);
    operationsList->setGeometry(10, 10, 320, 830);
    operationsList->setWordWrap(true);
    operationsList->setTextElideMode(Qt::ElideNone);
    operationsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    planeWidget = new Plane(central);
    planeWidget->setGeometry(340, 10, 530, 830);

    auto *tabsFrame = new QFrame(central);
    tabsFrame->setGeometry(880, 10, 410, 151);
    tabWidget = new QTabWidget(tabsFrame);
    tabWidget->setGeometry(10, 10, 390, 130);

    auto *modelTab = new QWidget(tabWidget);
    modelReprList = new QComboBox(modelTab);
    modelReprList->setGeometry(10, 50, 270, 40);
    modelReprList->addItem("Список точек и ребер");
    modelReprList->addItem("Матрица смежности");
    loadModelBtn = new QPushButton("Загрузить", modelTab);
    loadModelBtn->setGeometry(290, 10, 90, 80);
    tabWidget->addTab(modelTab, "Модель");

    auto *cameraTab = new QWidget(tabWidget);
    cameraTypeList = new QComboBox(cameraTab);
    cameraTypeList->setGeometry(10, 50, 270, 40);
    cameraTypeList->addItem("Стандартная");
    createCameraBtn = new QPushButton("Создать", cameraTab);
    createCameraBtn->setGeometry(290, 10, 90, 80);
    tabWidget->addTab(cameraTab, "Камера");

    auto *shiftFrame = new QFrame(central);
    shiftFrame->setGeometry(880, 550, 410, 80);
    dxOffsetInput = makeEdit(shiftFrame, "dX");
    dyOffsetInput = makeEdit(shiftFrame, "dY");
    dzOffsetInput = makeEdit(shiftFrame, "dZ");
    dxOffsetInput->setGeometry(10, 40, 90, 30);
    dyOffsetInput->setGeometry(105, 40, 90, 30);
    dzOffsetInput->setGeometry(200, 40, 90, 30);
    applyShiftBtn = new QPushButton("Применить", shiftFrame);
    applyShiftBtn->setGeometry(300, 40, 100, 30);
    undoBtn = new QPushButton("Отмена", shiftFrame);
    undoBtn->setGeometry(300, 8, 100, 30);

    auto *scaleFrame = new QFrame(central);
    scaleFrame->setGeometry(1090, 640, 200, 200);
    kScale = makeEdit(scaleFrame, "k");
    kScale->setGeometry(10, 80, 180, 30);
    applyScaleBtn = new QPushButton("Применить", scaleFrame);
    applyScaleBtn->setGeometry(10, 160, 180, 30);

    auto *rotateFrame = new QFrame(central);
    rotateFrame->setGeometry(880, 640, 200, 200);
    angleXRotate = makeEdit(rotateFrame, "angX");
    angleYRotate = makeEdit(rotateFrame, "angY");
    angleZRotate = makeEdit(rotateFrame, "angZ");
    angleXRotate->setGeometry(10, 40, 180, 30);
    angleYRotate->setGeometry(10, 80, 180, 30);
    angleZRotate->setGeometry(10, 120, 180, 30);
    applyRotateBtn = new QPushButton("Применить", rotateFrame);
    applyRotateBtn->setGeometry(10, 160, 180, 30);

    setActiveBtn = new QPushButton("Сделать активной", central);
    setActiveBtn->setGeometry(880, 170, 200, 30);
    composeBtn = new QPushButton("Сделать композит", central);
    composeBtn->setGeometry(1090, 170, 200, 30);

    tableWidget = new QTableWidget(central);
    tableWidget->setGeometry(880, 210, 410, 330);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"ID", "Имя", "Тип"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::createScene()
{
    auto scene = Facade::instance()->createGraphicsScene(
        static_cast<size_t>(planeWidget->width()),
        static_cast<size_t>(planeWidget->height()));
    if (!scene)
        return;
    scene->setBackgroundColor(39, 40, 41);

    auto qtScene = std::static_pointer_cast<QtGraphicsScene>(scene);
    if (!qtScene)
        return;
    planeWidget->setScene(qtScene->getRawScene());
    (void)Facade::instance()->createPainter(scene);
}

void MainWindow::insertRow(EntityId id, const QString &name, const QString &type)
{
    const int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
    tableWidget->setItem(row, 1, new QTableWidgetItem(name));
    tableWidget->setItem(row, 2, new QTableWidgetItem(type));
}

std::vector<int> MainWindow::selectedRows() const
{
    std::vector<int> rows;
    for (const auto &item : tableWidget->selectedItems())
    {
        if (item->column() == 0)
            rows.push_back(item->row());
    }
    std::sort(rows.begin(), rows.end());
    rows.erase(std::unique(rows.begin(), rows.end()), rows.end());
    return rows;
}

void MainWindow::onLoadModelBtnClicked()
{
    try
    {
        const QString path = QFileDialog::getOpenFileName(this, "Открыть файл", "",
            "Текстовые файлы (*.txt *.csv);;OBJ файлы (*.obj);;BIN файлы (*.bin)");
        if (path.isEmpty())
            return;

        const EntityStructureKind structureKind = modelReprList->currentIndex() == 0
            ? EntityStructureKind::ListCarcassModelStructure
            : EntityStructureKind::MatrixCarcassModelStructure;
        const auto id = objects;
        LoadRequest req{path.toStdString(), EntityKind::Model, structureKind};
        Facade::instance()->execute(std::make_shared<LoadCommand>(id, req));
        Facade::instance()->execute(std::make_shared<DrawCommand>());
        insertRow(objects++, QFileInfo(path).fileName(), "Каркас");
        logOperation("Загрузка модели: " + QFileInfo(path).fileName());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Ошибка загрузки", ex.what());
    }
}

void MainWindow::onShiftBtnClicked()
{
    bool okX = false, okY = false, okZ = false;
    const double dx = dxOffsetInput->text().toDouble(&okX);
    const double dy = dyOffsetInput->text().toDouble(&okY);
    const double dz = dzOffsetInput->text().toDouble(&okZ);
    if (!okX || !okY || !okZ)
    {
        QMessageBox::critical(this, "Ошибка", "Некорректные параметры переноса.");
        return;
    }
    MoveArgs args(dx, dy, dz);
    const auto rows = selectedRows();
    for (const int row : rows)
    {
        const auto id = tableWidget->item(row, 0)->text().toULongLong();
        Facade::instance()->execute(std::make_shared<EntityMoveCommand>(id, args));
    }
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    logOperation("Перенос выбранных объектов");
}

void MainWindow::onScaleBtnClicked()
{
    bool okK = false;
    const double k = kScale->text().toDouble(&okK);
    if (!okK || !std::isfinite(k) || std::abs(k) < 1e-9 || std::abs(k) > 10.0)
    {
        QMessageBox::critical(this, "Ошибка",
            "Некорректный коэффициент k. Допустимый диапазон: -10..-0.000000001 и 0.000000001..10.");
        return;
    }
    const auto rows = selectedRows();
    for (const int row : rows)
    {
        const auto id = static_cast<EntityId>(tableWidget->item(row, 0)->text().toULongLong());
        ScaleArgs args(k, 0.0, 0.0, 0.0);
        Facade::instance()->execute(std::make_shared<EntityScaleCommand>(id, args));
    }
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    logOperation("Масштабирование выбранных объектов");
}

void MainWindow::onRotateBtnClicked()
{
    bool okX = false, okY = false, okZ = false;
    const double ax = angleXRotate->text().toDouble(&okX);
    const double ay = angleYRotate->text().toDouble(&okY);
    const double az = angleZRotate->text().toDouble(&okZ);
    if (!okX || !okY || !okZ)
    {
        QMessageBox::critical(this, "Ошибка", "Некорректные параметры поворота.");
        return;
    }
    const auto rows = selectedRows();
    for (const int row : rows)
    {
        const auto id = static_cast<EntityId>(tableWidget->item(row, 0)->text().toULongLong());
        RotateArgs args(ax * M_PI / 180.0, ay * M_PI / 180.0, az * M_PI / 180.0,
            0.0, 0.0, 0.0);
        Facade::instance()->execute(std::make_shared<EntityRotateCommand>(id, args));
    }
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    logOperation("Поворот выбранных объектов");
}

void MainWindow::addCameraBtnClicked()
{
    Facade::instance()->execute(std::make_shared<CameraAddCommand>(objects));
    insertRow(objects++, "Камера", "Камера");
    logOperation("Создана новая камера");
}

void MainWindow::onUndoBtnClicked()
{
    const auto rows = selectedRows();
    if (rows.empty())
        return;

    for (const int row : rows)
    {
        const auto id = static_cast<EntityId>(tableWidget->item(row, 0)->text().toULongLong());
        Facade::instance()->execute(std::make_shared<EntityRestoreStateCommand>(id));
    }
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    logOperation("Undo выбранных объектов");
}

void MainWindow::onSetActiveBtnClicked()
{
    setActiveCamRequested();
}

void MainWindow::onComposeBtnClicked()
{
    composeRequested();
}

void MainWindow::contextMenuRequested(const QPoint &pos)
{
    const auto rows = selectedRows();
    if (rows.empty())
        return;

    QMenu menu(this);
    auto *deleteAction = menu.addAction("Удалить");
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteObjectRequested);
    if (rows.size() > 1)
    {
        auto *composeAction = menu.addAction("Создать композит");
        connect(composeAction, &QAction::triggered, this, &MainWindow::composeRequested);
    }
    else if (rows.size() == 1)
    {
        const auto type = tableWidget->item(rows.front(), 2)->text();
        if (type == "Камера")
        {
            auto *setActiveAction = menu.addAction("Установить активной");
            connect(setActiveAction, &QAction::triggered, this, &MainWindow::setActiveCamRequested);
        }
    }
    menu.exec(tableWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::deleteObjectRequested()
{
    auto rows = selectedRows();
    std::sort(rows.rbegin(), rows.rend());
    for (int row : rows)
    {
        const auto id = tableWidget->item(row, 0)->text().toULongLong();
        const auto type = tableWidget->item(row, 2)->text();
        if (type == "Камера" && id == activeCamId)
            continue;
        if (type == "Камера")
            Facade::instance()->execute(std::make_shared<CameraDeleteCommand>(id));
        else
            Facade::instance()->execute(std::make_shared<EntityDeleteCommand>(id));
        tableWidget->removeRow(row);
    }
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    logOperation("Удаление выбранных объектов");
}

void MainWindow::setActiveCamRequested()
{
    const auto rows = selectedRows();
    if (rows.size() != 1)
    {
        QMessageBox::information(this, "Камера", "Выберите ровно одну камеру.");
        return;
    }
    const auto type = tableWidget->item(rows.front(), 2)->text();
    if (type != "Камера")
    {
        QMessageBox::information(this, "Камера", "Активной можно сделать только камеру.");
        return;
    }
    const auto id = tableWidget->item(rows.front(), 0)->text().toULongLong();
    Facade::instance()->execute(std::make_shared<CameraSetActiveCommand>(id));
    activeCamId = id;
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    logOperation("Активная камера: ID " + QString::number(id));
}

void MainWindow::composeRequested()
{
    const auto rows = selectedRows();
    if (rows.size() < 2)
    {
        QMessageBox::information(this, "Композит", "Выберите минимум два объекта.");
        return;
    }

    std::vector<EntityId> ids;
    for (const int row : rows)
    {
        const auto type = tableWidget->item(row, 2)->text();
        if (type == "Камера")
            continue;
        ids.push_back(static_cast<EntityId>(tableWidget->item(row, 0)->text().toULongLong()));
    }

    bool created = false;
    Facade::instance()->execute(std::make_shared<EntityComposeCommand>(ids, created));
    if (!created)
    {
        QMessageBox::information(this, "Композит",
            "Для композита нужно минимум два некамерных объекта.");
        return;
    }

    insertRow(objects++, "Композит", "Композит");
    Facade::instance()->execute(std::make_shared<DrawCommand>());
    logOperation("Создан композит из выбранных объектов");
}

void MainWindow::logOperation(const QString &text)
{
    if (!operationsList)
        return;
    const QString stamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    operationsList->insertItem(0, "[" + stamp + "] " + text);
    while (operationsList->count() > 30)
        delete operationsList->takeItem(operationsList->count() - 1);
}
