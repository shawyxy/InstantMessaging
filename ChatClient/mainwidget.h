#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "./model/data.h"
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
};
#endif // MAINWIDGET_H
