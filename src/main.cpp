#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <map>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <string>

const std::string kStyleSheet = {
#include "stylesheet.dat"
};

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet(QString::fromStdString(kStyleSheet));
    w.show();
    return a.exec();
}