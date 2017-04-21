#include "mainwindow.h"
#include <QApplication>
#include "define.h"
#include <QDate>
#include "functionitemwidget.h"
#include"controlpanel.h"
#include "detectxml.h"

#define QDEBUG() qDebug()<<__FILE__<<__LINE__

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
