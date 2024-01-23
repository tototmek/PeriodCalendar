#include "core/calendar.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <map>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <string>

using namespace period_calendar;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    Calendar calendar;
    auto days = calendar.view();
}