#include "mainwindow.h"

#include "core/io.h"
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <fmt/core.h>
#include <map>
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
    try {
        calendar_.setPillStartDate(loadDate(kSavePath));
    } catch (std::runtime_error& e) {
    }
    initializeCalendarWidget();
    updateCalendarWidget();
    for (const auto& month : months) {
        monthComboBox_->addItem(QString::fromStdString(month));
    }
    handlePrevMonthButton();
    handleNextMonthButton();
    connect(monthComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::handleMonthComboBoxChange);
    connect(yearSpinBox_, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &MainWindow::handleYearSpinBoxChange);
    connect(nextMonthButton_, &QPushButton::clicked, this,
            &MainWindow::handleNextMonthButton);
    connect(prevMonthButton_, &QPushButton::clicked, this,
            &MainWindow::handlePrevMonthButton);
}

void MainWindow::handleMonthComboBoxChange(int index) {
    calendar_.setMonth(index);
    updateCalendarWidget();
}

void MainWindow::handleYearSpinBoxChange(int value) {
    calendar_.setYear(value);
    updateCalendarWidget();
}

void MainWindow::handleNextMonthButton() {
    auto newDate = calendar_.setNextMonth();
    monthComboBox_->setCurrentIndex(uint(newDate.month()) - 1);
    yearSpinBox_->setValue(int(newDate.year()));
}

void MainWindow::handlePrevMonthButton() {
    auto newDate = calendar_.setPrevMonth();
    monthComboBox_->setCurrentIndex(uint(newDate.month()) - 1);
    yearSpinBox_->setValue(int(newDate.year()));
}

void MainWindow::handleSetFirstPillDay(date::year_month_day date) {

    calendar_.setPillStartDate(date);
    updateCalendarWidget();
}

void MainWindow::handleApplicationQuit() {
    saveDate(calendar_.getPillStartDate(), kSavePath);
}

void MainWindow::initializeCalendarWidget() {
    auto grid = qobject_cast<QGridLayout*>(calendarWidget_->layout());
    const int rows = 6;
    const int columns = 7;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QPushButton* button = new QPushButton("0");
            button->setFixedSize(kDayWidth, kDayHeight);
            button->setFlat(true);
            QObject::connect(button, &QPushButton::clicked, [this, button]() {
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
                    this->handleSetFirstPillDay(date::year_month_day{
                        date::year(button->property("year").toInt()) /
                        button->property("month").toUInt() /
                        button->property("day").toUInt()});
                }
            });
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
            if (day->type == period_calendar::DayType::BLANK) {
                if (day->period == period_calendar::PeriodType::PERIOD) {
                    button->setStyleSheet(
                        QString::fromStdString(periodBlankDayStyleSheet));
                } else {
                    button->setStyleSheet(
                        QString::fromStdString(blankDayStyleSheet));
                }
            } else if (day->period == period_calendar::PeriodType::PERIOD) {
                button->setStyleSheet(
                    QString::fromStdString(periodDayStyleSheet));
            } else {
                button->setStyleSheet(
                    QString::fromStdString(normalDayStyleSheet));
            }
            ++day;
        }
    }
}