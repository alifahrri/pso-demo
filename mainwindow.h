#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contouritem.h"

#include "psoitem.h"

namespace Ui {
class MainWindow;
}

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PSO &pso, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ContourItem contour_item;
    PSOItem *pso_item;
    QTimer *timer;
};

#endif // MAINWINDOW_H
