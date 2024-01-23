#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

  private:
    Ui::MainWindow ui;
    QComboBox* monthComboBox_;
    QSpinBox* yearSpinBox_;
};

#endif // MAINWINDOW_H
