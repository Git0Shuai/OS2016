#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QString argv, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->lable_procInfo->setText(QString("I am %1").arg(argv));
  setWindowTitle(argv);
}

MainWindow::~MainWindow()
{
    delete ui;
}
