#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(PSO &pso, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pso_item(new PSOItem(pso)),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(QRectF(QPoint(-250,-250),QPoint(250,250)),this));
    ui->graphicsView->scene()->addItem(&contour_item);
    ui->graphicsView->scene()->addItem(pso_item);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    setFixedSize(550,575);
    setCentralWidget(ui->graphicsView);
    setWindowTitle("PSO Test");

    connect(timer,&QTimer::timeout,[=]
    {
        ui->graphicsView->scene()->update();
    });
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
