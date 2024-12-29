#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QPushButton>
#include <QWidget>


class MainWidget : public QWidget
{
    Q_OBJECT

private:
    static MainWidget* _instance;

    QWidget *windowLeft;         // 左侧窗口
    QWidget *windowMid;          // 中间窗口
    QWidget *windowRight;        // 右侧窗口

    QPushButton *userAvatar;     // 用户头像
    QPushButton *sesstonTabBtn;  // 会话标签按钮
    QPushButton *contactTabBtn;  // 联系人标签按钮
    QPushButton *applyTabBtn;    // 申请标签按钮

    void initMaindow();          // 初始化主窗口
    void initLeftWindow();       // 初始化左侧窗口
    void initMidWindow();        // 初始化中间窗口
    void initRightWindow();      // 初始化右侧窗口

public:
    static MainWidget* getInstance();
    ~MainWidget();
private:
    MainWidget(QWidget *parent = nullptr);
};
#endif // MAINWIDGET_H
