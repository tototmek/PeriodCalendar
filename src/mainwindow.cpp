#include "mainwindow.h"

#include <QLabel>
#include <QMessageBox>
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

const std::vector<std::string> monthsModified = {
    "stycznia", "lutego",   "marca",    "kwietnia",     "maja",      "czerwca",
    "lipca",    "sierpnia", "września", "października", "listopada", "grudnia"};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    this->setWindowTitle("Kalendarz Frosch");
    monthComboBox_ = ui.monthComboBox;
    yearSpinBox_ = ui.yearSpinBox;
    nextMonthButton_ = ui.nextMonthButton;
    prevMonthButton_ = ui.prevMonthButton;
    calendarWidget_ = ui.calendarWidget;
    initializeCalendarWidget();
    updateCalendarWidget();
    for (const auto& month : months) {
        monthComboBox_->addItem(QString::fromStdString(month));
    }
    connect(monthComboBox_, SIGNAL(currentIndexChanged(int)), this,
            SLOT(handleMonthComboBoxChange(int)));
    connect(yearSpinBox_, SIGNAL(valueChanged(int)), this,
            SLOT(handleYearSpinBoxChange(int)));
    connect(nextMonthButton_, SIGNAL(clicked()), this,
            SLOT(handleNextMonthButton()));
    connect(prevMonthButton_, SIGNAL(clicked()), this,
            SLOT(handlePrevMonthButton()));
}

void MainWindow::handleMonthComboBoxChange(int index) {
    spdlog::info("Month changed: {}", index);
    calendar_.setMonth(index);
    updateCalendarWidget();
}

void MainWindow::handleYearSpinBoxChange(int value) {
    spdlog::info("Year changed: {}", value);
    calendar_.setYear(value);
    updateCalendarWidget();
}

void MainWindow::handleNextMonthButton() {
    spdlog::info("Next month");
    auto newDate = calendar_.setNextMonth();
    monthComboBox_->setCurrentIndex(uint(newDate.month()) - 1);
    yearSpinBox_->setValue(int(newDate.year()));
}

void MainWindow::handlePrevMonthButton() {
    spdlog::info("Prev month");
    auto newDate = calendar_.setPrevMonth();
    monthComboBox_->setCurrentIndex(uint(newDate.month()) - 1);
    yearSpinBox_->setValue(int(newDate.year()));
}

void MainWindow::initializeCalendarWidget() {
    auto grid = qobject_cast<QGridLayout*>(calendarWidget_->layout());
    const int rows = 6;
    const int columns = 7;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QPushButton* button = new QPushButton("0");
            button->setFixedSize(kDayWidth, kDayHeight);
            QObject::connect(button, &QPushButton::clicked, [this, button]() {
                spdlog::info("Day clicked: {}/{}/{}",
                             button->property("day").toUInt(),
                             button->property("month").toUInt(),
                             button->property("year").toInt());
                auto reply = QMessageBox(
                    QMessageBox::Question, "Ustawianie daty",
                    fmt::format(
                        "Czy chcesz ustawić {} {} {}\njako dzień "
                        "pierwszej tabletki w cyklu?",
                        button->property("day").toUInt(),
                        monthsModified[button->property("month").toUInt() - 1],
                        button->property("year").toInt())
                        .c_str(),
                    QMessageBox::No | QMessageBox::Yes, this);
                reply.setButtonText(QMessageBox::Yes, tr("Tak"));
                reply.setButtonText(QMessageBox::No, tr("Nie"));
                if (reply.exec() == QMessageBox::Yes) {
                    spdlog::info("Set fist pill day");
                }
            });
            button->setProperty("day", 30);
            button->setProperty("month", 9);
            button->setProperty("year", 2001);
            grid->addWidget(button, row + 1, col);
        }
    }
    calendarWidget_->setLayout(grid);
}

void MainWindow::updateCalendarWidget() {
    const int rows = 6;
    const int columns = 7;
    auto day = calendar_.view().begin();
    auto grid = qobject_cast<QGridLayout*>(calendarWidget_->layout());
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QLayoutItem* layoutItem = grid->itemAtPosition(row + 1, col);
            auto button = qobject_cast<QPushButton*>(layoutItem->widget());
            button->setText(QString::number(uint(day->date.day())));
            button->setProperty("day", uint(day->date.day()));
            button->setProperty("month", uint(day->date.month()));
            button->setProperty("year", int(day->date.year()));
            ++day;
        }
    }
}