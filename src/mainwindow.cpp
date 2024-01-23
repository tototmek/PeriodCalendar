#include "mainwindow.h"
#include <QLabel>
#include <QString>
#include <map>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

const std::map<std::string, uint> monthsMap = {
    {"Styczeń", 1},  {"Luty", 2},         {"Marzec", 3},    {"Kwiecień", 4},
    {"Maj", 5},      {"Czerwiec", 6},     {"Lipiec", 7},    {"Sierpień", 8},
    {"Wrzesień", 9}, {"Październik", 10}, {"Listopad", 11}, {"Grudzień", 12}};

const std::vector<std::string> months = {
    "Styczeń", "Luty",     "Marzec",   "Kwiecień",    "Maj",      "Czerwiec",
    "Lipiec",  "Sierpień", "Wrzesień", "Październik", "Listopad", "Grudzień"};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    this->setWindowTitle("Kalendarz Frosch");
    monthComboBox_ = ui.monthComboBox;
    yearSpinBox_ = ui.yearSpinBox;

    for (const auto& month : months) {
        monthComboBox_->addItem(QString::fromStdString(month));
    }

    connect(monthComboBox_, SIGNAL(currentIndexChanged(int)), this,
            SLOT(handleMonthComboBoxChange(int)));

    connect(yearSpinBox_, SIGNAL(valueChanged(int)), this,
            SLOT(handleYearSpinBoxChange(int)));
}

void MainWindow::handleMonthComboBoxChange(int index) {
    spdlog::info("Month changed: {}", index);
}

void MainWindow::handleYearSpinBoxChange(int value) {
    spdlog::info("Year changed: {}", value);
}