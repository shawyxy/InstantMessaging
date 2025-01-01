#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget *w = MainWidget::getInstance();
    w->show();
    qDebug() << "hello";
    return a.exec();
}
