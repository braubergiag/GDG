#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "dialogmodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadCounterPlot(QCustomPlot * customPLot);
    QCustomPlot * createCounterPlot();

private slots:
    void on_actionSet_Model_triggered();

private:


    Ui::MainWindow *ui;
    Model * model_ = nullptr;
    QCustomPlot * counterPlot_ = nullptr;
};
#endif // MAINWINDOW_H
