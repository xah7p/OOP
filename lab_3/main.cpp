#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion");
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
