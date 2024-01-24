#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core/calendar_wrapper.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

  public slots:
    void handleMonthComboBoxChange(int index);
    void handleYearSpinBoxChange(int value);
    void handleNextMonthButton();
    void handlePrevMonthButton();

  private:
    period_calendar::CalendarWrapper calendar_;
    Ui::MainWindow ui;
    QComboBox* monthComboBox_;
    QSpinBox* yearSpinBox_;
    QAbstractButton* nextMonthButton_;
    QAbstractButton* prevMonthButton_;
    QWidget* calendarWidget_;
};

#endif // MAINWINDOW_H
