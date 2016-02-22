#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->lable_procInfo->setText("I am the original process!");
  ui->pushButton_fork->setEnabled(false);
  setWindowTitle("original process");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_fork_clicked(){
    //now on parent process before fork.
    //lineEdit_childProcessName->test() is the child process name which is going to fork.
    //windowTitle() is the current process name.
    while(fork() == -1);
    if(!fork()){ 
        //now we are on child process after fork.
        //lineEdit_childProcessName->test() becomes the current process name
        //so reset windowtitle and show it
        this->ui->lable_procInfo->setText(QString("I am %1.\nmy parent process is %2")
                                    .arg(ui->lineEdit_childProcName->text()) 
                                    .arg(windowTitle()));
        this->setWindowTitle(ui->lineEdit_childProcName->text());
        //now we are on child process,clear lineEdit.
        this->ui->lineEdit_childProcName->clear();
        this->show();
        return;
    }
    else{
        //here is parent process.
        QMessageBox Msg;
        Msg.setWindowTitle("Result");
        Msg.setText(QString("Creat process %1").arg(ui->lineEdit_childProcName->text()));
        Msg.exec();
        return;
    }
}

void MainWindow::on_lineEdit_childProcName_textChanged(const QString &arg1)
{
    if(ui->lineEdit_childProcName->text().isEmpty())
       ui->pushButton_fork->setEnabled(false);
    else
       ui->pushButton_fork->setEnabled(true);
    return;
}
