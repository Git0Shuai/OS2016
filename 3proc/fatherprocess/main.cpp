#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString procname;
    if(argc == 1 && QString(argv[0]) == "./process"){
      if(!fork()){
          execl("./process", "child1", NULL);
          return 1;
      }   
      if(!fork()){
          execl("./process", "child2", NULL);
          return 2;
      }
      procname = "original process";
    }
    else
      procname = argv[0];
    MainWindow w(procname);
    w.show();

    return a.exec();
}
