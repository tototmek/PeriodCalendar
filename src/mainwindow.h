#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core/calendar_wrapper.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QMainWindow>

constexpr int kDayWidth = 30;
constexpr int kDayHeight = 30;

const std::string normalDayStyleSheet = "color: #cccccc;";
const std::string blankDayStyleSheet = "color: #484848;";
const std::string periodDayStyleSheet = "color: #88dd88;";
const std::string periodBlankDayStyleSheet = "color: #294029;";

const std::string kSavePath = "save.dat";

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

  public slots:
    void handleMonthComboBoxChange(int index);
    void handleYearSpinBoxChange(int value);
    void handleNextMonthButton();
    void handlePrevMonthButton();
    void handleSetFirstPillDay(date::year_month_day date);
    void handleApplicationQuit();

  private:
    void initializeCalendarWidget();
    void updateCalendarWidget();
    period_calendar::CalendarWrapper calendar_;
    Ui::MainWindow ui;
    QComboBox* monthComboBox_;
    QSpinBox* yearSpinBox_;
    QAbstractButton* nextMonthButton_;
    QAbstractButton* prevMonthButton_;
    QWidget* calendarWidget_;
};

#endif // MAINWINDOW_H
