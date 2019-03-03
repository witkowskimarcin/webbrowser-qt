#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWebEngine::initialize();
    MainWindow w;
    w.show();


    return a.exec();
}
