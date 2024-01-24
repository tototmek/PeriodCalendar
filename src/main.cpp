#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <map>
#include <string>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QObject::connect(&a, &QCoreApplication::aboutToQuit, &w,
                     &MainWindow::handleApplicationQuit);
    w.show();
    return a.exec();
}